//
// Created by camix on 10/6/20.
//

#include <iostream>
#include "ManagerJuego.h"
#include "../../commons/protocols/protocolo.h"
#include "../../commons/utils/Constantes.h"

ManagerJuego::ManagerJuego() {
    ManagerJuego::informacionNivel = {0}; // TODO patch para race conditions
    ManagerJuego::managerVista = new ManagerVista({}, 0, PANTALLA_ANCHO, PANTALLA_ALTO);
}

void ManagerJuego::estadoNivel(nlohmann::json instruccion) {
    if (instruccion["tipoMensaje"] == INFORMACION_NIVEL) setInformacionNivel(instruccion);
    else if (instruccion["tipoMensaje"] == ESTADO_TICK) setEstadoTick(instruccion);
    else if (instruccion["tipoMensaje"] == ESTADO_LOGIN) setEstadoLogin(instruccion);
}

void ManagerJuego::setEstadoTick(nlohmann::json mensaje) {
    struct EstadoTick estado;
    estado.nuevoNivel = mensaje["numeroNivel"];
    int i = 0;
    for (; i < MAX_JUGADORES; i++ ) {
        estado.estadosJugadores[i].helper1.posicionX = mensaje["estadosJugadores"][i]["helper1"]["posicionX"];
        estado.estadosJugadores[i].helper1.posicionY = mensaje["estadosJugadores"][i]["helper1"]["posicionY"];
        estado.estadosJugadores[i].helper1.angulo = mensaje["estadosJugadores"][i]["helper1"]["angulo"];
        estado.estadosJugadores[i].helper2.posicionX = mensaje["estadosJugadores"][i]["helper2"]["posicionX"];
        estado.estadosJugadores[i].helper2.posicionY = mensaje["estadosJugadores"][i]["helper2"]["posicionY"];
        estado.estadosJugadores[i].helper2.angulo = mensaje["estadosJugadores"][i]["helper2"]["angulo"];
        estado.estadosJugadores[i].posicionX = mensaje["estadosJugadores"][i]["posicionX"];
        estado.estadosJugadores[i].posicionY = mensaje["estadosJugadores"][i]["posicionY"];
    }
    int j = 0;
    for (; j < MAX_ENEMIGOS; j++ ){
        estado.estadosEnemigos[j].posicionX = mensaje["estadosEnemigos"][j]["posicionX"];
        estado.estadosEnemigos[j].posicionY = mensaje["estadosEnemigos"][j]["posicionY"];
        estado.estadosEnemigos[j].clase = mensaje["estadosEnemigos"][j]["clase"];
    }
    ManagerJuego::estadoTick = estado;
}

void ManagerJuego::setInformacionNivel(nlohmann::json mensaje) {
    struct InformacionNivel info;

    info.numeroNivel = mensaje["numeroNivel"];
    info.velocidad = mensaje["velocidad"];
    strcpy(info.informacionFinNivel, std::string(mensaje["informacionFinNivel"]).c_str());
    for (int i = 0; i < MAX_FONDOS ; i++){
        info.informacionFondo[i].pVelocidad = mensaje["informacionFondo"][i]["velocidad"];
        strcpy(info.informacionFondo[i].pFondo, std::string(mensaje["informacionFondo"][i]["fondo"]).c_str());
    }
    ManagerJuego::informacionNivel = info;
}

void ManagerJuego::setEstadoLogin(nlohmann::json mensaje) {
    struct EstadoLogin estadoLogin;

    estadoLogin.nroJugador = mensaje["nroJugador"];
    estadoLogin.estadoLogin = mensaje["estadoLogin"];
    std::string jugador1 = mensaje["jugador1"];
    strcpy(estadoLogin.jugador1, jugador1.c_str());
    std::string jugador2 = mensaje["jugador2"];
    strcpy(estadoLogin.jugador2, jugador2.c_str());
    std::string jugador3 = mensaje["jugador3"];
    strcpy(estadoLogin.jugador3, jugador3.c_str());
    std::string jugador4 = mensaje["jugador4"];
    strcpy(estadoLogin.jugador4, jugador4.c_str());

    ManagerJuego::estadoLogin = estadoLogin;
}

void ManagerJuego::setEstadoLogin(struct EstadoLogin estadoLogin) {
    ManagerJuego::estadoLogin.nroJugador = estadoLogin.nroJugador;
    ManagerJuego::estadoLogin.estadoLogin = estadoLogin.estadoLogin;
    strcpy(ManagerJuego::estadoLogin.jugador1, estadoLogin.jugador1);
    strcpy(ManagerJuego::estadoLogin.jugador2, estadoLogin.jugador2);
    strcpy(ManagerJuego::estadoLogin.jugador3, estadoLogin.jugador3);
    strcpy(ManagerJuego::estadoLogin.jugador4, estadoLogin.jugador4);
}

void ManagerJuego::render(){
    managerVista->setInformacionNivel(informacionNivel);
    //Render texture to screen
    managerVista->render(estadoTick, estadoLogin);
}

// TODO: che no da
bool ManagerJuego::terminoJuego() {
    return informacionNivel.numeroNivel > 3;
}

// TODO: che tampoco da
bool ManagerJuego::enJuego() {
    return estadoLogin.estadoLogin == LOGIN_FIN;
}