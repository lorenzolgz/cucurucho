//
// Created by lorenzo on 6/21/20.
//

#include "HiloAceptadorConexiones.h"

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

    HiloOrquestadorPartida* hiloOrquestadorPartida = new HiloOrquestadorPartida(config, hilosConexionesServidores);

    hiloOrquestadorPartida->start();

    // Aceptar reconexiones
    try {
        atenderPosiblesReconexiones(conexionesServidores);
    }
    catch (const std::exception &e) {
        l->error("Ocurrio un error al atender las reconexiones. No se aceptaran mas reconexiones");
		l->error(e.what());
    }

	hiloOrquestadorPartida->join();
	for (auto* conexionServidor : *conexionesServidores) {
		conexionServidor->cerrar();
	}
	aceptadorConexiones->dejarDeEscuchar();
}

void HiloAceptadorConexiones::atenderPosiblesReconexiones(std::list<ConexionServidor *> *conexionesServidores){

    while (true) {
        auto *conexionServidor = aceptadorConexiones->aceptarConexion();
        ControladorDeSesiones *controladorDeSesiones = new ControladorDeSesiones(
				conexionServidor,
				conexionesServidores,
				conexionesServidores->size() + 1,
				true);
        if (!controladorDeSesiones->iniciarSesion()) { // Si entró un usuario no registrado
            continue;
        }

        conexionesServidores->push_back(conexionServidor);
        for (HiloConexionServidor *c : *hilosConexionesServidores) {
            if (c->username == conexionServidor->getUsuario()) {
                nlohmann::json json;
                json["tipoMensaje"] = ESTADO_LOGIN;
                json["estadoLogin"] = LOGIN_FIN;
                json["nroJugador"] = c->conexionServidor->getNroJugador();
                json["jugador1"] = "";
                json["jugador2"] = "";
                json["jugador3"] = "";
                json["jugador4"] = "";

                try {
                    conexionServidor->enviarMensaje(json);
                } catch (const std::exception &e) {
                    l->error("HiloAceptador, rechazando a cliente reconectado: " + std::string(e.what()));
                    conexionServidor->cerrar();
                    conexionesServidores->pop_back();
                    break;
                }

                c->conexionServidor->setClientSocket(conexionServidor->getClientSocket());
            }
        }
        reinstanciarListaConexiones(conexionesServidores);
    }
}

void HiloAceptadorConexiones::reinstanciarListaConexiones(std::list<ConexionServidor*>* conexionesServidores) {
    while (!conexionesServidores->empty()) {
        conexionesServidores->pop_back();
    }
    for (HiloConexionServidor* c : *hilosConexionesServidores) {
        conexionesServidores->push_back(c->conexionServidor);
    }
}

void HiloAceptadorConexiones::notificarEstadoConexion(std::list<ConexionServidor*>* conexionesServidores, int estadoLogin) {
	// !!!!! abstraerr
    nlohmann::json json;
    json["tipoMensaje"] = ESTADO_LOGIN;
    json["estadoLogin"] = estadoLogin;
    json["jugador1"] = "\0";
    json["jugador2"] = "\0";
    json["jugador3"] = "\0";
    json["jugador4"] = "\0";

    int i = 1;
    for (ConexionServidor* & c : *conexionesServidores) {
        json["jugador" + std::to_string(i)] = c->getUsuario();
        i++;
    }

    i = 1;
    auto iteradorConexionServidor = conexionesServidores->begin();
    while (iteradorConexionServidor != conexionesServidores->end()) {
        try {
            json["nroJugador"] = i;
            (*iteradorConexionServidor)->enviarMensaje(json);
            iteradorConexionServidor++;
            i++;
        } catch (const ConexionExcepcion& e) {
        	l->error("Un usuario se desconecto antes de que empiece la partida");
            // Si el usuario se desconecta antes de comenzar la partida puede conectarse otro (evaluar?)
            conexionesServidores->erase(iteradorConexionServidor);
            // Volver a enviar mensajes con lista actualizada
            notificarEstadoConexion(conexionesServidores, estadoLogin);
            return;
        }
    }
}

std::list<HiloConexionServidor*>* HiloAceptadorConexiones::crearHilosConexionesServidores(std::list<ConexionServidor*>* conexionesServidores) {
    auto* nuevoHilosConexionesServidores = new std::list<HiloConexionServidor*>();

    int i = 0;
    for (auto* conexionServidor : *(conexionesServidores)) {
        auto* hiloConexionServidor = new HiloConexionServidor(conexionServidor, conexionServidor->getNroJugador(), conexionServidor->getUsuario(), aceptadorConexiones);
        hiloConexionServidor->start();
        nuevoHilosConexionesServidores->push_back(hiloConexionServidor);
        i++;
    }
    return nuevoHilosConexionesServidores;
}
