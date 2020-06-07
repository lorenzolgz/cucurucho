#include "ConexionServidor.h"
#include <unistd.h>
#include <iostream>

ConexionServidor::ConexionServidor(int client_socket) {
	ConexionServidor::client_socket = client_socket;
}

nlohmann::json ConexionServidor::recibirMensaje() {
	return recibirData2(client_socket);
}

void ConexionServidor::enviarEstadoTick(struct EstadoTick* estadoTick) {
	if (enviarData<struct EstadoTick>(&client_socket, estadoTick) < 0) {
		perror("Send Data Error");
		exit(1);
	}
}

void ConexionServidor::enviarInformacionNivel(struct InformacionNivel* informacionNivel) {
	if (enviarData<struct InformacionNivel>(&client_socket, informacionNivel) < 0) {
		perror("Send Data Error");
		exit(1);
	}
}

void ConexionServidor::cerrar() {
	close(client_socket);
}

void ConexionServidor::enviarEstadoLogin(bool esCorrecta) {
    if (enviarData<bool>(&client_socket, &esCorrecta) < 0) {
        perror("Send Data Error");
        exit(1);
    }
}
