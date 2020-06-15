#include "HiloOrquestadorPartida.h"
#include "../../commons/utils/Log.h"
#include "HiloConexionServidor.h"
#include "../../commons/ColaBloqueante.h"

void initializeData(struct EstadoTick* estadoTick);
void processData(Partida* partida, struct Comando comandos[], struct EstadoTick* estadoTick, struct InformacionNivel* informacionNivel);
int esperarConexiones(int puerto, Configuracion* config);
Configuracion* parsearConfiguracion();

std::string usuariosPorID[MAX_JUGADORES];
int usuarioConectado[MAX_JUGADORES];


HiloOrquestadorPartida::HiloOrquestadorPartida(Configuracion *config, std::list<ConexionServidor*>* conexiones) {
	this->config = config;
	this->conexiones = conexiones;
	this->partida = new Partida(config);

}

void desconectarUsuario(std::string usuarioPerdido, std::list<HiloConexionServidor*>* hilos , HiloConexionServidor* hiloADesconectar){
    hilos->remove(hiloADesconectar);
    hiloADesconectar->activo = false;
    bool anotado = false;
    for(int i=0; i<MAX_JUGADORES && !anotado; i++){
        if(!usuariosPorID[i].compare(usuarioPerdido)){
            usuarioConectado[i] = 0;
            anotado = true;
            break;
        }
    }
    if(!anotado){
        l->error("Ocurrio un error al procesar que el jugador " + usuarioPerdido + " perdio su conexion");
        throw new std::exception();
    }
    l->info("Se perdio la conexion con el usuario " + usuarioPerdido);
    throw new std::exception();
}

void reconectarUsuario(std::string usuarioPerdido, HiloConexionServidor* hiloADesconectar){
    hiloADesconectar->activo = true;
    bool anotado = false;
    for(int i=0; i<MAX_JUGADORES && !anotado; i++){
        if(!usuariosPorID[i].compare(usuarioPerdido)){
            usuarioConectado[i] = 1;
            anotado = true;
            break;
        }
    }
    if(!anotado){
        l->error("Ocurrio un error al procesar que el jugador " + usuarioPerdido + " retomo su conexion");
        throw new std::exception();
    }
    l->info("Se retomo la conexion con el usuario " + usuarioPerdido);
    throw new std::exception();
}

void receiveData(std::list<HiloConexionServidor*>* hilosConexionesServidores, struct Comando *comandos) {
    hilosConexionesServidores->reverse();

    std::string usuarioPerdido;

    try {
        // Uno de los clientes se queda esperando al resto, por eso siempre unos se ven mejor y otros peor.
        for (auto* hiloConexionServidor : *(hilosConexionesServidores)) {
            // Solo opero sobre hilos activos
            if(hiloConexionServidor->activo){
                auto* colaReceptora = hiloConexionServidor->colaReceptora;
                nlohmann::json mensajeJson;

                while (colaReceptora->size() > MAX_COLA_RECEPTORA_SERVIDOR) {
                    mensajeJson = colaReceptora->pop();
                    if(mensajeJson["_t"] == ERROR_CONEXION){
                        usuarioPerdido = mensajeJson["usuario"];
                        desconectarUsuario(usuarioPerdido, hilosConexionesServidores, hiloConexionServidor);
                    }
                }

                if(colaReceptora->size() > 0 && hiloConexionServidor->activo){
                    mensajeJson = colaReceptora->pop();

                    if(mensajeJson["_t"] == ERROR_CONEXION){
                        usuarioPerdido = mensajeJson["usuario"];
                        desconectarUsuario(usuarioPerdido, hilosConexionesServidores, hiloConexionServidor);
                    }
                    else if (mensajeJson["_t"] == COMANDO) {
                        struct Comando comando = {mensajeJson["nroJugador"], mensajeJson["arriba"], mensajeJson["abajo"], mensajeJson["izquierda"], mensajeJson["derecha"]};
                        comandos[comando.nroJugador-1] = comando;
                    }
                    else if (mensajeJson["_t"] == RECONEXION) {
                        usuarioPerdido = mensajeJson["usuario"];
                        reconectarUsuario(usuarioPerdido, hiloConexionServidor);
                    } else {
                        l->error("HiloOrquestadorPartida. Recibiendo mensaje invalido");
                    }
                }
            }
        }
    }
    catch(...) {
        // TODO: Algo mas para hacer tras eliminar al jugador de la lista y marcarlo como no presente?
        //l->info("Ocurrio un error al recibir los movimientos de los jugadores");
        //l->info(excepcion.what());
    }


    // !!!! Dejo esta linea aca porque es muy buena
	/*
		struct Comando comando = comandos[i];
		if (comando.arriba || comando.abajo || comando.izquierda || comando.derecha) {
			huboMovimientos = true;
			l->error("!!!!! " + std::to_string(comando.nroJugador) + " | " + std::to_string(comando.arriba) + " - " + std::to_string(comando.abajo) + " - " + std::to_string(comando.izquierda) + " - " + std::to_string(comando.derecha));
			*/
}

void sendData(std::list<HiloConexionServidor*>* hilosConexionesServidores, struct InformacionNivel* informacionNivel, struct EstadoTick* estadoTick, int* nuevoNivel) {
	if (*nuevoNivel) {
		l->debug("Nuevo nivel enviando : " + std::to_string(informacionNivel->numeroNivel));
	}
	if (*nuevoNivel) {
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

std::list<HiloConexionServidor*>* crearHilosConexionesServidores(std::list<ConexionServidor*>* conexiones) {
	auto* hilosConexionesServidores = new std::list<HiloConexionServidor*>();

	int i = 0;
	for (auto* conexion : *(conexiones)) {
        usuariosPorID[i] = conexion->getUsuario();
        usuarioConectado[i] = 1;
		auto* hiloConexionServidor = new HiloConexionServidor(conexion, i);
		hiloConexionServidor->start();
		hilosConexionesServidores->push_back(hiloConexionServidor);
		i++;
	}
	return hilosConexionesServidores;
}

void HiloOrquestadorPartida::run() {
	l->info("Comenzando a correr HiloOrquestadorPartida con " + std::to_string(conexiones->size()) + " jugadores.");
	bool quit = false;
	struct Comando comandos[conexiones->size()];
	struct InformacionNivel informacionNivel;
	struct EstadoTick estadoTick;
	bool terminoNivelActual = false;
	clock_t t2, t1 = clock();

	int commands_count = 0;
	initializeData(&estadoTick);
	// Todo esto es necesario?
	informacionNivel.numeroNivel = 0;
	// Comunicacion inicial.
	int nuevoNivel = 1;

	std::list<HiloConexionServidor*>* hilosConexionesServidores = crearHilosConexionesServidores(conexiones);

	//keep communicating with client
	try {
		while (!quit) {

			t2 = clock();
			if ((t2 - t1) > 1000 * 1000 / 60) { // TODO jugar con estos valores afecta la performance, yo toco el ultimo nro para que sea divisor de 1 tick cada 60 sec.
			} else {
				continue;
			}

			for (int i = 0; i < hilosConexionesServidores->size(); i++) {
				comandos[i] = {0, 0, 0, 0, 0};
			}
			// Receive data (command)
			receiveData(hilosConexionesServidores, comandos);
            //--------------------
			// Process model
			processData(partida, comandos, &estadoTick, &informacionNivel);
            //--------------------
			// Send data (view)
            sendData(hilosConexionesServidores, &informacionNivel, &estadoTick, &nuevoNivel);
			//--------------------

			t1 = clock();
		}
	}
	catch (...) {
        // TODO stoppear hilosConexionesServidores
        // Si se llegó aca, quiere decir que no se pudo catchear la desconexion dentro de receiveData
        l->error("HiloOrquestadorPartida. Ocurrio un error en el main loop");
	}

	for (auto* hiloConexionServidor : *(hilosConexionesServidores)) {
		hiloConexionServidor->join();
	}

	l->info("Terminando de correr HiloOrquestadorPartida");
}

void processData(Partida* partida, struct Comando comandos[], struct EstadoTick* estadoTick, struct InformacionNivel* informacionNivel) {
	EstadoInternoNivel estadoInternoNivel = partida->state(informacionNivel);
	partida->tick(comandos);

	// Seteando estadoTick
	estadoTick->nuevoNivel = estadoInternoNivel.nuevoNivel;
	EstadoInternoCampoMovil estadoCampoMovil = estadoInternoNivel.estadoCampoMovil;
	int i = 0;
	for (EstadoJugador estadoJugador : estadoCampoMovil.estadosJugadores) {
		estadoTick->estadosJugadores[i] = estadoJugador;
		// Asumiendo que el orden es el mismo que el del inicio de la partida
		estadoTick->estadosJugadores[i].presente = usuarioConectado[i];
		i++;
	}
	i = 0;
	for (EstadoEnemigo estadoEnemigo : estadoCampoMovil.estadosEnemigos) {
		estadoTick->estadosEnemigos[i] = estadoEnemigo;
		i++;
	}
	// !!!! hardcodeadisimo
	for (; i < MAX_ENEMIGOS; i++) {
		estadoTick->estadosEnemigos[i].clase = 0;
	}
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

	for (int i = 0; i < MAX_ENEMIGOS; i++) {
		estadoTick->estadosEnemigos[i].clase = 0;
	}
}
