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
    ManagerJuego::estadoLogin = {LOGIN_PENDIENTE};
}

void ManagerJuego::render(){
    managerVista->setInformacionNivel(informacionNivel);
    //Render texture to screen
    managerVista->render(estadoTick, estadoLogin, username);
}

// TODO: che no da
bool ManagerJuego::terminoJuego() {
    return informacionNivel.numeroNivel > 3;
}

// TODO: che tampoco da
bool ManagerJuego::enJuego() {
    return estadoLogin.estadoLogin == LOGIN_FIN;
}

void ManagerJuego::setInformacionNivel(const InformacionNivel &informacionNivel) {
    ManagerJuego::informacionNivel = informacionNivel;
}

void ManagerJuego::setUsername(const std::string &username) {
    ManagerJuego::username = username;
}

void ManagerJuego::setEstadoTick(const EstadoTick &estadoTick) {
    ManagerJuego::estadoTick = estadoTick;
}

void ManagerJuego::setEstadoLogin(const EstadoLogin &estadoLogin) {
    ManagerJuego::estadoLogin = estadoLogin;
}
