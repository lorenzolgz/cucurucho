//
// Created by lorenzo on 6/21/20.
//

#include "HiloAceptadorConexiones.h"

HiloAceptadorConexiones::HiloAceptadorConexiones(
        std::list<ConexionServidor*>* conexiones,
        std::list<HiloConexionServidor*>* hiloConexiones,
        AceptadorConexiones* aceptadorConexiones) {
    this->conexiones = conexiones;
    this->hiloConexiones = hiloConexiones;
    this->aceptadorConexiones = aceptadorConexiones;

}

void HiloAceptadorConexiones::run() {

    // TODO ¿Aceptar las n conexiones primero aca tambien? (Esto implicaria instanciar a HiloOrquestador desde acá)

    // Aceptar reconexiones
    try {
        atenderPosiblesReconexiones(conexiones, hiloConexiones, aceptadorConexiones);
    }
    catch(...){
        l->error("Ocurrio un error al atender las reconexiones, se reintentará escucharlas nuevamente");
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