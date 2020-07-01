#include "ConexionServidor.h"
#include "ConexionExcepcion.h"
#include <unistd.h>
#include <iostream>

ConexionServidor::ConexionServidor(int client_socket) {
	ConexionServidor::client_socket = client_socket;
}

nlohmann::json ConexionServidor::recibirMensaje() {
	return recibirData2(client_socket);
}

void ConexionServidor::enviarMensaje(nlohmann::json mensaje) {
	return enviarData2(client_socket, mensaje);
}

void ConexionServidor::enviarEstadoLogin(struct EstadoLogin estadoLogin) {
	nlohmann::json json;

    json["tipoMensaje"] = ESTADO_LOGIN;
	json["estadoLogin"] = estadoLogin.estadoLogin;
    json["nroJugador"] = estadoLogin.nroJugador;
    json["cantidadJugadores"] = estadoLogin.cantidadJugadores;
	for (int i = 0; i < MAX_JUGADORES; i++) {
	    json["jugadores"][i] = std::string(estadoLogin.jugadores[i]);
	}

    enviarMensaje(json);
}

// Para enviar el EstadoLogin sin el arreglo de jugadores
void ConexionServidor::enviarEstadoLoginSimple(int estadoLogin, int nroJugador) {
    struct EstadoLogin estado{};
    estado.estadoLogin = estadoLogin;
    estado.nroJugador = nroJugador;
    estado.cantidadJugadores = 0;
    for (auto & jugador : estado.jugadores) {
        jugador[0] = '\0';
    }

    enviarEstadoLogin(estado);
}

void ConexionServidor::cerrar() {
	close(client_socket);
}

const std::string &ConexionServidor::getUsuario() const {
    return usuario;
}

void ConexionServidor::setUsuario(const std::string &usuario) {
    ConexionServidor::usuario = usuario;
}

void ConexionServidor::setNroJugador(int nroJugador) {
    ConexionServidor::nroJugador = nroJugador;
}

int ConexionServidor::getNroJugador() const {
    return nroJugador;
}

int ConexionServidor::getClientSocket() const {
    return client_socket;
}

void ConexionServidor::setClientSocket(int clientSocket) {
    client_socket = clientSocket;
}

void ConexionServidor::enableTimeout() {
    struct timeval tv;
    tv.tv_sec = TIMEOUT_MENSAJES;
    tv.tv_usec = 0;
    assert(setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv) >= 0);
    assert(setsockopt(client_socket, SOL_SOCKET, SO_SNDTIMEO, (const char*)&tv, sizeof tv) >= 0);
}
