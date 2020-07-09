#include "HiloOrquestadorPartida.h"
#include "HiloConexionServidor.h"

void initializeData(struct EstadoTick* estadoTick);
bool processData(Partida *partida, Comando comandos[], EstadoTick *estadoTick, InformacionNivel *informacionNivel,
                 std::list<HiloConexionServidor *> *pList);
int esperarConexiones(int puerto, Configuracion* config);


HiloOrquestadorPartida::HiloOrquestadorPartida(Configuracion *config, std::list<HiloConexionServidor*>* hilosConexionesServidores, AceptadorConexiones* aceptadorConexiones) {
	this->partida = new Partida(config);
	this->config = config;
	this->hilosConexionesServidores = hilosConexionesServidores;
	this->aceptadorConexiones = aceptadorConexiones;
	this->quit = false;
}


void receiveData(std::list<HiloConexionServidor *> *hilosConexionesServidores, Comando *comandos,
                 Configuracion *config) {
    hilosConexionesServidores->reverse();

    std::string usuarioPerdido;

    try {
        // Uno de los clientes se queda esperando al resto, por eso siempre unos se ven mejor y otros peor.
        for (auto* hiloConexionServidor : *(hilosConexionesServidores)) {
            // Solo opero sobre hilos activos
            if(hiloConexionServidor->activo){
                auto* colaReceptora = hiloConexionServidor->colaReceptora;
                nlohmann::json mensajeJson;

                while (colaReceptora->size() > config->getMaxColaReceptora()) {
                    mensajeJson = colaReceptora->pop();
                }

                if(colaReceptora->size() > 0 && hiloConexionServidor->activo){
                    mensajeJson = colaReceptora->pop();

                    if (mensajeJson["_t"] == COMANDO) {
                        int nroJugador = hiloConexionServidor->conexionServidor->getNroJugador();
                        struct Comando comando = {nroJugador, mensajeJson["arriba"], mensajeJson["abajo"], mensajeJson["izquierda"], mensajeJson["derecha"], mensajeJson["disparo"]};
                        comandos[nroJugador - 1] = comando;
                    } else {
                        l->error("HiloOrquestadorPartida. Recibiendo mensaje invalido");
                    }
                }
            }
        }
    }
    catch(const std::exception &e) {
        // TODO: Algo mas para hacer tras eliminar al jugador de la lista y marcarlo como no presente?
        l->error("Ocurrio un error al recibir los movimientos de los jugadores");
        l->error(e.what());
    }
}

void sendData(std::list<HiloConexionServidor*>* hilosConexionesServidores, struct InformacionNivel* informacionNivel, struct EstadoTick* estadoTick, int* nuevoNivel) {
    if (*nuevoNivel) {
		l->debug("Nuevo nivel enviando : " + std::to_string(informacionNivel->numeroNivel));
	}
	if (*nuevoNivel && estadoTick->numeroNivel != FIN_DE_JUEGO) {
		for (auto *hiloConexionServidor : *(hilosConexionesServidores)) {
			hiloConexionServidor->enviarInformacionNivel(informacionNivel);
		}
		*nuevoNivel = false;
	} else {
		for (auto *hiloConexionServidor : *(hilosConexionesServidores)) {
            hiloConexionServidor->enviarEstadoTick(estadoTick);
		}
		*nuevoNivel = estadoTick->nuevoNivel;
	}
}

void HiloOrquestadorPartida::run() {
	l->info("Comenzando a correr HiloOrquestadorPartida con " + std::to_string(hilosConexionesServidores->size()) + " jugadores.");
	quit = false;
	struct Comando comandos[hilosConexionesServidores->size()];
	struct InformacionNivel informacionNivel;
	struct EstadoTick estadoTick;
	bool terminoNivelActual = false;
	clock_t t2, t1 = clock();
	clock_t entreNiveles = clock();

	int commands_count = 0;
	initializeData(&estadoTick);
	// Todo esto es necesario?
	informacionNivel.numeroNivel = 0;
	// Comunicacion inicial.
	int nuevoNivel = 1;

    for (int i = 0; i < hilosConexionesServidores->size(); i++) {
        comandos[i] = {0, 0, 0, 0, 0};
    }

	//keep communicating with client
	try {
		while (!quit) {

			t2 = clock();
			if ((t2 - t1) > 1000 * 1000 / 60) { // TODO jugar con estos valores afecta la performance, yo toco el ultimo nro para que sea divisor de 1 tick cada 60 sec.
			} else {
				continue;
			}

			// Receive data (command)
            receiveData(hilosConexionesServidores, comandos, config);
            if (clock() < entreNiveles) { // Si los clientes estan viendo la pantalla intermedia, no procesar comandos.
                for (int i = 0; i < hilosConexionesServidores->size(); i++) {
                    comandos[i] = {0, 0, 0, 0, 0};
                }
            }
            //--------------------
			// Process model
            quit |= processData(partida, comandos, &estadoTick, &informacionNivel, hilosConexionesServidores);

            //--------------------
			// Send data (view)
            sendData(hilosConexionesServidores, &informacionNivel, &estadoTick, &nuevoNivel);
			//--------------------
            if (quit) {
                break;
            }

            if (nuevoNivel) {
                entreNiveles = clock() + TIMEOUT_PROXIMO_NIVEL * CLOCKS_PER_SEC;
            }

			t1 = clock();
		}
	}
	catch (const std::exception &e) {
        l->error("HiloOrquestadorPartida. Ocurrio un error en el main loop.");
        l->error(e.what());
	}

	l->info("Esperando que terminen los hilosConexionesServidores.");
	for (auto* hiloConexionServidor : *(hilosConexionesServidores)) {
	    // TODO: Por que doble enviarEstadoTick? Para evitar race conditions donde se cierre el hilo antes de enviarse
	    // Habria que cambiarse por un sistema mas elegante
		hiloConexionServidor->enviarEstadoTick(&estadoTick);
		hiloConexionServidor->enviarEstadoTick(&estadoTick);
		hiloConexionServidor->terminar();
	}

	for (auto* hiloConexionServidor : *(hilosConexionesServidores)) {
		hiloConexionServidor->join();
	}
	l->info("Terminaron todos los hilosConexionesServidores.");

    aceptadorConexiones->shutdownSocket();

	l->info("Terminando de correr HiloOrquestadorPartida.");
}

bool HiloOrquestadorPartida::termino() {
	return quit;
}

bool processData(Partida *partida, Comando comandos[], EstadoTick *estadoTick, InformacionNivel *informacionNivel,
                 std::list<HiloConexionServidor *> *conexiones) {
	EstadoInternoNivel estadoInternoNivel = partida->state(informacionNivel);
	partida->tick(comandos);

    // Seteando estadoTick
    estadoTick->nuevoNivel = estadoInternoNivel.nuevoNivel;
    estadoTick->numeroNivel = estadoInternoNivel.nivel;

	if (partida->termino()) {
        estadoTick->nuevoNivel = FIN_DE_JUEGO; estadoTick->numeroNivel = FIN_DE_JUEGO;
		l->info("La partida finalizo");
		return true;
	}

	EstadoInternoCampoMovil estadoCampoMovil = estadoInternoNivel.estadoCampoMovil;
	estadoTick->posX = estadoCampoMovil.posX;
	int i = 0;
	for (EstadoJugador estadoJugador : estadoCampoMovil.estadosJugadores) {
		estadoTick->estadosJugadores[i] = estadoJugador;
		i++;
	}

	for (HiloConexionServidor* h : *conexiones) {
	    estadoTick->estadosJugadores[h->jugador - 1].presente = h->activo;
	}

	estadoTick->estadosEnemigos = estadoCampoMovil.estadosEnemigos;
	return false;
}


void initializeData(struct EstadoTick* estadoTick) {
	for (int i = 0; i < MAX_JUGADORES; i++) {
		estadoTick->estadosJugadores[i].posicionX = -1000;
		estadoTick->estadosJugadores[i].posicionY = -1000;
        estadoTick->estadosJugadores[i].presente = 0;
        estadoTick->estadosJugadores[i].helper1.posicionX = -1000;
		estadoTick->estadosJugadores[i].helper1.posicionY = -1000;
		estadoTick->estadosJugadores[i].helper2.posicionX = -1000;
		estadoTick->estadosJugadores[i].helper2.posicionY = -1000;
	}
}
