//
// Created by lorenzo on 6/21/20.
//

#include "HiloAceptadorConexiones.h"

HiloAceptadorConexiones::HiloAceptadorConexiones(
        int puerto,
        Configuracion* config) {
    this->puerto = puerto;
    this->config = config;
    this->aceptadorConexiones = new AceptadorConexiones(puerto);

}

void HiloAceptadorConexiones::run() {

    aceptadorConexiones->escuchar();

    std::list<ConexionServidor*> listaDeConexiones;
    this->conexiones = &listaDeConexiones;

    while (conexiones->size() < config->getCantidadJugadores()) { //usuario != usuarioPerdido
        l->info("Esperando usuario(s)");
        auto* conexionServidor = aceptadorConexiones->aceptarConexion();
        ControladorDeSesiones* controladorDeSesiones = new ControladorDeSesiones(conexionServidor, conexiones,
                                                                                 conexiones->size() + 1,
                                                                                 false);
        if (!controladorDeSesiones->iniciarSesion()) {//si entró un usuario no registrado
            continue;
        }
        conexiones->push_back(conexionServidor);
        notificarEstadoConexion(conexiones, LOGIN_ESPERAR);
        l->info("Usuario " + std::to_string(conexiones->size()) + " conectado");
    }
    l->info("Todos los usuarios fueron aceptados");
    notificarEstadoConexion(conexiones, LOGIN_COMENZAR);

    // TODO: Pre-procesamiento?
    std::this_thread::sleep_for(std::chrono::seconds(TIMEOUT_LOGIN_FIN));
    notificarEstadoConexion(conexiones, LOGIN_FIN);

    this->hiloConexiones = crearHilosConexionesServidores(conexiones, aceptadorConexiones);

    HiloOrquestadorPartida* hiloOrquestadorPartida = new HiloOrquestadorPartida(config, hiloConexiones);

    hiloOrquestadorPartida->start();

    // Aceptar reconexiones
    try {
        atenderPosiblesReconexiones(conexiones, hiloConexiones, aceptadorConexiones);
    }
    catch(...){
        l->error("Ocurrio un error al atender las conexiones");
        for (auto* conexion : *this->conexiones) {
            conexion->cerrar();
        }
        aceptadorConexiones->dejarDeEscuchar();
        atenderPosiblesReconexiones(conexiones, hiloConexiones, aceptadorConexiones);
    }


}

void HiloAceptadorConexiones::atenderPosiblesReconexiones(std::list<ConexionServidor *> *conexiones,
    std::list<HiloConexionServidor *> *hiloConexiones,
    AceptadorConexiones* aceptadorConexiones){

    while (true) {
        auto *conexionServidor = aceptadorConexiones->aceptarConexion();
        ControladorDeSesiones *controladorDeSesiones = new ControladorDeSesiones(
                conexionServidor,
                conexiones,
                conexiones->size() + 1,
                true);
        if (!controladorDeSesiones->iniciarSesion()) {//si entró un usuario no registrado
            continue;
        }

        conexiones->push_back(conexionServidor);
        for (HiloConexionServidor *c : *hiloConexiones) {
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
                } catch (const std::exception &exc) {
                    l->error("HiloAceptador, rechazando a cliente reconectado: " + std::string(exc.what()));
                    conexionServidor->cerrar();
                    conexiones->pop_back();
                    break;
                }

                c->conexionServidor->setClientSocket(conexionServidor->getClientSocket());
            }
        }
        reinstanciarListaConexiones(conexiones, hiloConexiones);
    }
}

void HiloAceptadorConexiones::reinstanciarListaConexiones(std::list<ConexionServidor*>* conexiones, std::list<HiloConexionServidor*>* hiloConexiones) {
    while (!conexiones->empty()) {
        conexiones->pop_back();
    }
    for (HiloConexionServidor* c : *hiloConexiones) {
        conexiones->push_back(c->conexionServidor);
    }
}

void HiloAceptadorConexiones::notificarEstadoConexion(std::list<ConexionServidor*>* conexiones, int estadoLogin) {
    nlohmann::json json;
    json["tipoMensaje"] = ESTADO_LOGIN;
    json["estadoLogin"] = estadoLogin;
    json["jugador1"] = "\0";
    json["jugador2"] = "\0";
    json["jugador3"] = "\0";
    json["jugador4"] = "\0";

    int i = 1;
    for (ConexionServidor* & c : *conexiones) {
        json["jugador" + std::to_string(i)] = c->getUsuario();
        i++;
    }

    i = 1;
    auto j = conexiones->begin();
    while (j != conexiones->end()) {
        try {
            json["nroJugador"] = i;
            (*j)->enviarMensaje(json);
            j++;
            i++;
        } catch (const ConexionExcepcion& e) {
            // Si el usuario se desconecta antes de comenzar la partida puede conectarse otro (evaluar?)
            conexiones->erase(j);
            // Volver a enviar mensajes con lista actualizada
            notificarEstadoConexion(conexiones, estadoLogin);
            return;
        }
    }
}

std::list<HiloConexionServidor*>* HiloAceptadorConexiones::crearHilosConexionesServidores(std::list<ConexionServidor*>* conexiones,
                                                                 AceptadorConexiones* aceptadorConexiones) {
    auto* hilosConexionesServidores = new std::list<HiloConexionServidor*>();

    int i = 0;
    for (auto* conexion : *(conexiones)) {
        auto* hiloConexionServidor = new HiloConexionServidor(conexion, conexion->getNroJugador(), conexion->getUsuario(), aceptadorConexiones);
        hiloConexionServidor->start();
        hilosConexionesServidores->push_back(hiloConexionServidor);
        i++;
    }
    return hilosConexionesServidores;
}