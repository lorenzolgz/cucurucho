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

    nlohmann::json mensajeJson;
    mensajeJson["tipoMensaje"] = ESTADO_TICK;
    mensajeJson["numeroNivel"] = estadoTick->nuevoNivel;
    int i = 0, j = 0;
    for (; i< MAX_JUGADORES; i++){
        mensajeJson["estadosJugadores"][i]["helper1"]["posicionX"] = estadoTick->estadosJugadores[i].helper1.posicionX;
        mensajeJson["estadosJugadores"][i]["helper1"]["posicionY"] = estadoTick->estadosJugadores[i].helper1.posicionY;
        mensajeJson["estadosJugadores"][i]["helper1"]["angulo"] = estadoTick->estadosJugadores[i].helper1.angulo;
        mensajeJson["estadosJugadores"][i]["helper2"]["posicionX"] = estadoTick->estadosJugadores[i].helper2.posicionX;
        mensajeJson["estadosJugadores"][i]["helper2"]["posicionY"] = estadoTick->estadosJugadores[i].helper2.posicionY;
        mensajeJson["estadosJugadores"][i]["helper2"]["angulo"] = estadoTick->estadosJugadores[i].helper2.angulo;
        mensajeJson["estadosJugadores"][i]["posicionX"] = estadoTick->estadosJugadores[i].posicionX;
        mensajeJson["estadosJugadores"][i]["posicionY"] = estadoTick->estadosJugadores[i].posicionY;
    }
    for (; j< MAX_ENEMIGOS; j++){
        mensajeJson["estadosEnemigos"][j]["posicionX"] = estadoTick->estadosEnemigos[j].posicionX;
        mensajeJson["estadosEnemigos"][j]["posicionY"] = estadoTick->estadosEnemigos[j].posicionY;
        mensajeJson["estadosEnemigos"][j]["clase"] = estadoTick->estadosEnemigos[j].clase;
    }
    enviarData2(client_socket,mensajeJson);

}

void ConexionServidor::enviarInformacionNivel(struct InformacionNivel* informacionNivel) {

    nlohmann::json mensajeJson = {
            {"tipoMensaje", INFORMACION_NIVEL},
            {"numeroNivel",  informacionNivel->numeroNivel},
            {"velocidad", informacionNivel->velocidad},
            {"informacionFinNivel",   informacionNivel->informacionFinNivel}
    };
    for ( int i = 0 ; i < MAX_FONDOS ; i++ ){
        mensajeJson["informacionFondo"][i]["velocidad"] = informacionNivel->informacionFondo[i].pVelocidad;
        mensajeJson["informacionFondo"][i]["fondo"] = informacionNivel->informacionFondo[i].pFondo;
    }
    enviarData2(client_socket,mensajeJson);
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
