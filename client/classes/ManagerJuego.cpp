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

void ManagerJuego::setInformacionNivel(){
    managerVista->setInformacionNivel(reinterpret_cast<const InformacionNivel &>(informacionNivel));
    //Render texture to screen
    managerVista->render(reinterpret_cast<const EstadoTick &>(estadoTick));
}

// TODO: che no da
bool ManagerJuego::terminoJuego() {
    return informacionNivel.numeroNivel > 3;
}
