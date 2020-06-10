#include "ConexionCliente.h"
#include <unistd.h>
#include <iostream>

ConexionCliente::ConexionCliente(int client_socket) {
	ConexionCliente::server_socket = client_socket;
}


nlohmann::json ConexionCliente::recibirMensaje() {
     return recibirData2(server_socket);

}

struct EstadoTick ConexionCliente::recibirEstadoTick() {
	struct EstadoTick estadoTick;

	l->debug("Cliente por recibir mensaje");
	if (recibirData<struct EstadoTick>(&server_socket, &estadoTick) < 0) {
		perror("Receive Data Error");
		exit(1);
	}

	l->debug("Cliente recibio estadoTick.estadoJugador.posicionX: " + std::to_string(estadoTick.estadosJugadores[0].posicionX));

	return estadoTick;
}

struct InformacionNivel ConexionCliente::recibirInformacionNivel() {
	struct InformacionNivel informacionNivel;

	l->debug("Cliente por recibir mensaje");
	if (recibirData<struct InformacionNivel>(&server_socket, &informacionNivel) < 0) {
		perror("Receive Data Error");
		exit(1);
	}

	l->debug("Cliente recibio informacionNivel: ");

	return informacionNivel;
}

void ConexionCliente::enviarComando(struct Comando* comando) {
	l->debug("Cliente por mandar mensaje: " + std::to_string(comando->arriba) + " " + std::to_string(comando->abajo) + " " + std::to_string(comando->izquierda)  + " " + std::to_string(comando->derecha));

	nlohmann::json mensajeJson = {
			{"arriba",    comando->arriba},
			{"abajo",     comando->abajo},
			{"izquierda", comando->izquierda},
			{"derecha",   comando->derecha}
	};

	enviarData2(server_socket, mensajeJson);
}

void ConexionCliente::cerrar() {
	close(server_socket);
}

bool ConexionCliente::contraseniaCorrecta() {
    bool esCorrecta = false;

    l->debug("Cliente por recibir mensaje");
    if (recibirData<bool>(&server_socket, &esCorrecta) < 0) {
        perror("Receive Data Error");
        //exit(1);
    }

    l->debug("Cliente contrasenia correcta: " + std::to_string(esCorrecta));
    return esCorrecta;
}

void ConexionCliente::enviarDatosDeLogin(struct Login *logueo) {
    l->debug("Cliente por mandar credenciales");

    nlohmann::json mensajeJson = {
            {"usuario",    logueo->usuario},
            {"contrasenia",     logueo->contrasenia}
    };

    enviarData2(server_socket, mensajeJson);

}
