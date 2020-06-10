#include "ConexionCliente.h"
#include <unistd.h>
#include <iostream>

ConexionCliente::ConexionCliente(int client_socket) {
	ConexionCliente::server_socket = client_socket;
}


nlohmann::json ConexionCliente::recibirMensaje() {
     return recibirData2(server_socket);

}

void ConexionCliente::setEstadoTick(struct EstadoTick *estadoTick, nlohmann::json mensaje) {
    estadoTick->nuevoNivel = mensaje["numeroNivel"];
    int i = 0;
    for (; i < MAX_JUGADORES; i++ ) {
        estadoTick->estadosJugadores[i].helper1.posicionX = mensaje["estadosJugadores"][i]["helper1"]["posicionX"];
        estadoTick->estadosJugadores[i].helper1.posicionY = mensaje["estadosJugadores"][i]["helper1"]["posicionY"];
        estadoTick->estadosJugadores[i].helper1.angulo = mensaje["estadosJugadores"][i]["helper1"]["angulo"];
        estadoTick->estadosJugadores[i].helper2.posicionX = mensaje["estadosJugadores"][i]["helper2"]["posicionX"];
        estadoTick->estadosJugadores[i].helper2.posicionY = mensaje["estadosJugadores"][i]["helper2"]["posicionY"];
        estadoTick->estadosJugadores[i].helper2.angulo = mensaje["estadosJugadores"][i]["helper2"]["angulo"];
        estadoTick->estadosJugadores[i].posicionX = mensaje["estadosJugadores"][i]["posicionX"];
        estadoTick->estadosJugadores[i].posicionY = mensaje["estadosJugadores"][i]["posicionY"];

    }
    int j = 0;
    for (; j < MAX_ENEMIGOS; j++ ){
        estadoTick->estadosEnemigos[j].posicionX = mensaje["estadosEnemigos"][j]["posicionX"];
        estadoTick->estadosEnemigos[j].posicionY = mensaje["estadosEnemigos"][j]["posicionY"];
        estadoTick->estadosEnemigos[j].clase = mensaje["estadosEnemigos"][j]["clase"];
    }
}

void ConexionCliente::setInformacionNivel(struct InformacionNivel *informacionNivel, nlohmann::json mensaje) {
    informacionNivel->numeroNivel = mensaje["numeroNivel"];
    informacionNivel->velocidad = mensaje["velocidad"];
    strcpy(informacionNivel->informacionFinNivel, std::string(mensaje["informacionFinNivel"]).c_str());
    for (int i = 0; i < MAX_FONDOS ; i++){
        informacionNivel->informacionFondo[i].pVelocidad = mensaje["informacionFondo"][i]["velocidad"];
        strcpy(informacionNivel->informacionFondo[i].pFondo, std::string(mensaje["informacionFondo"][i]["fondo"]).c_str());
    }
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
