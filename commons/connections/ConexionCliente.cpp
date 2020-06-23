#include "ConexionCliente.h"
#include "ConexionExcepcion.h"
#include <unistd.h>
#include <iostream>

ConexionCliente::ConexionCliente(int client_socket) {
	ConexionCliente::client_socket = client_socket;
}

nlohmann::json ConexionCliente::recibirMensaje() {
     return recibirData2(client_socket);
}

void ConexionCliente::enviarComando(struct Comando* comando) {
	l->debug("Cliente por mandar mensaje: " + std::to_string(comando->arriba) + " " + std::to_string(comando->abajo) +
			 " " + std::to_string(comando->izquierda) + " " + std::to_string(comando->derecha));

	nlohmann::json mensajeJson = {
			{"_t", COMANDO},
			{"nroJugador", comando->nroJugador},
			{"arriba",     comando->arriba},
			{"abajo",      comando->abajo},
			{"izquierda",  comando->izquierda},
			{"derecha",    comando->derecha}
	};

	l->debug("enviarComando " + mensajeJson.dump());

	enviarData2(client_socket, mensajeJson);
}

void ConexionCliente::cerrar() {
	close(client_socket);
}


void ConexionCliente::enviarDatosDeLogin(struct Login *logueo) {
    l->debug("Cliente por mandar credenciales");

    nlohmann::json mensajeJson = {
            {"usuario",    logueo->usuario},
            {"contrasenia",     logueo->contrasenia}
    };

    enviarData2(client_socket, mensajeJson);
}
