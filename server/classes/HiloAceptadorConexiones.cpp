//
// Created by lorenzo on 6/21/20.
//

#include "HiloAceptadorConexiones.h"
#include "../../commons/connections/AceptarConexionExcepcion.h"

HiloAceptadorConexiones::HiloAceptadorConexiones(int puerto, Configuracion* config) {
	this->config = config;
    this->aceptadorConexiones = new AceptadorConexiones(puerto);
}

void HiloAceptadorConexiones::run() {

    aceptadorConexiones->escuchar();

    std::list<ConexionServidor*>* conexionesServidores = new std::list<ConexionServidor*>();

    while (conexionesServidores->size() < config->getCantidadJugadores()) { // Usuario != usuarioPerdido
        l->info("Esperando usuario(s)");
        auto* conexionServidor = aceptadorConexiones->aceptarConexion();
        ControladorDeSesiones* controladorDeSesiones = new ControladorDeSesiones(conexionServidor, conexionesServidores,
																				 conexionesServidores->size() + 1,
																				 false);
        if (!controladorDeSesiones->iniciarSesion()) { // Si entró un usuario no registrado
            continue;
        }
        conexionesServidores->push_back(conexionServidor);
        notificarEstadoConexion(conexionesServidores, LOGIN_ESPERAR);
        l->info("Usuario " + std::to_string(conexionesServidores->size()) + " conectado");
    }
    l->info("Todos los usuarios fueron aceptados");
    notificarEstadoConexion(conexionesServidores, LOGIN_COMENZAR);

    // TODO: Pre-procesamiento?
    std::this_thread::sleep_for(std::chrono::seconds(TIMEOUT_LOGIN_FIN));
    notificarEstadoConexion(conexionesServidores, LOGIN_FIN);

    this->hilosConexionesServidores = crearHilosConexionesServidores(conexionesServidores);

    HiloOrquestadorPartida* hiloOrquestadorPartida = new HiloOrquestadorPartida(config, hilosConexionesServidores, aceptadorConexiones);

    hiloOrquestadorPartida->start();

    try {
		aceptarPosiblesReconexiones(hiloOrquestadorPartida);
    }
    catch (const std::exception &e) {
        l->error("Ocurrio un error al aceptar las reconexiones. No se aceptaran mas reconexiones");
		l->error(e.what());
    }

	hiloOrquestadorPartida->join();
	for (auto* conexionServidor : *conexionesServidores) {
		conexionServidor->cerrar();
	}

	aceptadorConexiones->dejarDeEscuchar();
}

void HiloAceptadorConexiones::aceptarPosiblesReconexiones(HiloOrquestadorPartida* hiloOrquestadorPartida){
	std::list<ConexionServidor*>* conexionesServidores = extraerConexionesDeHilosConexionesServidores();

    while (true) {
		ConexionServidor* conexionServidor;
    	try {
			conexionServidor = aceptadorConexiones->aceptarConexion();
		} catch (const AceptarConexionExcepcion &ace) {
    		// Esto se necesita porque cuando termina la partida, la solucion para que deje de aceptar es que
    		// se cierre violentamente el socket aceptador.
    		if (hiloOrquestadorPartida->termino()) {
				l->info("Ya no se escuchan mas reconexiones.");
				return;
			} else {
    			throw ace;
    		}
		}

    	l->info("Se acepto una potencial reconexion.");

        ControladorDeSesiones *controladorDeSesiones = new ControladorDeSesiones(
				conexionServidor,
				conexionesServidores,
				conexionesServidores->size() + 1,
				true);
        if (!controladorDeSesiones->iniciarSesion()) { // Si entró un usuario no registrado
            continue;
        }

        for (HiloConexionServidor *h : *hilosConexionesServidores) {
            if (h->username == conexionServidor->getUsuario()) {
                try {
					conexionServidor->enviarEstadoLoginSimple(LOGIN_FIN, h->conexionServidor->getNroJugador());
                } catch (const std::exception &e) {
                    l->error("HiloAceptadorConexiones. rechazando a cliente reconectado: " + std::string(e.what()));
                    conexionServidor->cerrar();
                    break;
                }

                l->debug("Reemplazando socket " + std::to_string(h->conexionServidor->getClientSocket()) +
                	" por el socket " + std::to_string(conexionServidor->getClientSocket()) +
                	" del usuario " + h->username);
                h->conexionServidor->setClientSocket(conexionServidor->getClientSocket());
            }
        }
    }
}

void HiloAceptadorConexiones::notificarEstadoConexion(std::list<ConexionServidor*>* conexionesServidores, int tipoEstadoLogin) {
    std::string arregloJugadores[MAX_JUGADORES];
    for (auto & jugador : arregloJugadores) {
        jugador = "";
    }

    int i = 0;
    for (ConexionServidor* & c : *conexionesServidores) {
        arregloJugadores[i] = c->getUsuario();
        i++;
    }

    i = 0;
    auto iteradorConexionServidor = conexionesServidores->begin();
    while (iteradorConexionServidor != conexionesServidores->end()) {
        try {
			struct EstadoLogin estadoLogin;
			estadoLogin.estadoLogin = tipoEstadoLogin;
			estadoLogin.nroJugador = i + 1;
			estadoLogin.cantidadJugadores = config->getCantidadJugadores();
			for (int j = 0; j < MAX_JUGADORES; j++) {
			    strcpy(estadoLogin.jugadores[j], arregloJugadores[j].c_str());
			}

			(*iteradorConexionServidor)->enviarEstadoLogin(estadoLogin);
			iteradorConexionServidor++;
            i++;
        } catch (const ConexionExcepcion& e) {
        	l->error("Un usuario se desconecto antes de que empiece la partida");
            // Si el usuario se desconecta antes de comenzar la partida puede conectarse otro (evaluar?)
            conexionesServidores->erase(iteradorConexionServidor);
            // Volver a enviar mensajes con lista actualizada
            notificarEstadoConexion(conexionesServidores, tipoEstadoLogin);
            return;
        }
    }
}

std::list<HiloConexionServidor*>* HiloAceptadorConexiones::crearHilosConexionesServidores(std::list<ConexionServidor*>* conexionesServidores) {
    auto* nuevoHilosConexionesServidores = new std::list<HiloConexionServidor*>();

    int i = 0;
    for (auto* conexionServidor : *(conexionesServidores)) {
        auto* hiloConexionServidor = new HiloConexionServidor(conexionServidor, conexionServidor->getNroJugador(), conexionServidor->getUsuario());
        hiloConexionServidor->start();
        nuevoHilosConexionesServidores->push_back(hiloConexionServidor);
        i++;
    }
    return nuevoHilosConexionesServidores;
}

std::list<ConexionServidor*>* HiloAceptadorConexiones::extraerConexionesDeHilosConexionesServidores() {
	std::list<ConexionServidor*>* conexionesServidores = new std::list<ConexionServidor*>();

	for (auto* h : *hilosConexionesServidores) {
		conexionesServidores->push_back(h->conexionServidor);
	}

	return conexionesServidores;
}