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

	// TODO: unificarlo con el enviar estado del main
    json["tipoMensaje"] = ESTADO_LOGIN;
    json["nroJugador"] = estadoLogin.nroJugador;
    json["estadoLogin"] = estadoLogin.estadoLogin;
    json["jugador1"] = "\0";
    json["jugador2"] = "\0";
    json["jugador3"] = "\0";
    json["jugador4"] = "\0";
    enviarMensaje(json);
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
