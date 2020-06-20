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

// "Siempre" va a funcionar porque se llama apenas se inicia la conexion
struct EstadoLogin ConexionCliente::recibirEstadoLogin() {
	uint32_t nroJugador = false;

    l->debug("Cliente por recibir mensaje");
    if (recibirData<uint32_t>(&client_socket, &nroJugador) < 0) {
        perror("Receive Data Error");
        throw ConexionExcepcion();
    }

    l->debug("Cliente contrasenia correcta: " + std::to_string(nroJugador));
	struct EstadoLogin estadoLogin = { (int) nroJugador };
    return estadoLogin;
}


// "Siempre" va a funcionar porque se llama apenas se inicia la conexion
void ConexionCliente::enviarDatosDeLogin(struct Login *logueo) {
    l->debug("Cliente por mandar credenciales");

    nlohmann::json mensajeJson = {
            {"usuario",    logueo->usuario},
            {"contrasenia",     logueo->contrasenia}
    };

    enviarData2(client_socket, mensajeJson);
}
