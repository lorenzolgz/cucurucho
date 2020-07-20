#include "HiloOrquestadorPartida.h"
#include "HiloConexionServidor.h"

bool processData(Partida *partida, Comando comandos[], EstadoTick *estadoTick, InformacionNivel *informacionNivel,
                 std::list<HiloConexionServidor *> *pList, int* nuevoNivel);
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
                        struct Comando comando = {nroJugador, mensajeJson["arriba"], mensajeJson["abajo"], mensajeJson["izquierda"], mensajeJson["derecha"], mensajeJson["disparo"], mensajeJson["invencible"]};
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
		*nuevoNivel = false;
		if (estadoTick->numeroNivel != FIN_DE_JUEGO) {
			for (auto *hiloConexionServidor : *(hilosConexionesServidores)) {
				hiloConexionServidor->enviarInformacionNivel(informacionNivel);
			}
		}
	} else {
		for (auto *hiloConexionServidor : *(hilosConexionesServidores)) {
            hiloConexionServidor->enviarEstadoTick(estadoTick);
		}
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
	clock_t tiempoNivelInt = clock();

	int commands_count = 0;
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

			// Si los clientes estan viendo la pantalla intermedia, no procesar datos.
            if (clock() > tiempoNivelInt) {
				// Process model
				quit |= processData(partida, comandos, &estadoTick, &informacionNivel, hilosConexionesServidores, &nuevoNivel);
            }

            if (nuevoNivel && informacionNivel.numeroNivel != 1) {
                tiempoNivelInt = clock() + TIMEOUT_PROXIMO_NIVEL * CLOCKS_PER_SEC;
            }

			// Send data (view)
            sendData(hilosConexionesServidores, &informacionNivel, &estadoTick, &nuevoNivel);
            if (quit) {
                break;
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
                 std::list<HiloConexionServidor *> *conexiones, int* nuevoNivel) {

	EstadoInternoNivel estadoInternoNivel = partida->state(informacionNivel);
	*nuevoNivel = estadoInternoNivel.nuevoNivel;
	estadoTick->nuevoNivel = estadoInternoNivel.nuevoNivel;
	estadoTick->numeroNivel = estadoInternoNivel.nivel;

    // Seteando estadoTick

	EstadoInternoCampoMovil estadoCampoMovil = estadoInternoNivel.estadoCampoMovil;
	estadoTick->posX = estadoCampoMovil.posX;
	int i = 0;
	for (EstadoJugador estadoJugador : estadoCampoMovil.estadosJugadores) {
		estadoTick->estadosJugadores[i] = estadoJugador;
		strcpy(estadoTick->estadosJugadores[i].usuario, "");
		i++;
	}

	for (HiloConexionServidor* h : *conexiones) {
	    estadoTick->estadosJugadores[h->jugador - 1].presente = h->activo;
		strcpy(estadoTick->estadosJugadores[h->jugador - 1].usuario, h->username.c_str());
	}

	estadoTick->estadosEnemigos = estadoCampoMovil.estadosEnemigos;
	estadoTick->estadosDisparos = estadoCampoMovil.estadosDisparos;
	estadoTick->estadosDisparosEnemigos = estadoCampoMovil.estadosDisparosEnemigos;

	if (partida->termino()) {
		estadoTick->nuevoNivel = FIN_DE_JUEGO; estadoTick->numeroNivel = FIN_DE_JUEGO;
		l->info("La partida finalizo");
		return true;
	}
	partida->tick(comandos);

	return false;
}
