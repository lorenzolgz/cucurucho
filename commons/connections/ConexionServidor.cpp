#include "ConexionServidor.h"
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
	uint32_t nroJugadorNormalizado = estadoLogin.nroJugador;
	if (enviarData<uint32_t>(&client_socket, &nroJugadorNormalizado) < 0) {
		perror("Send Data Error");
		exit(1);
	}
}

void ConexionServidor::cerrar() {
	close(client_socket);
}
