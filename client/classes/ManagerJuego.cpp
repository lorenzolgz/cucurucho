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
    ManagerJuego::estadoTick.numeroNivel = 0;
    ManagerJuego::estadoTick.nuevoNivel = 0;

    Audio *audio = Audio::getInstance();
    ManagerJuego::audioPerder = audio->generarEfecto("sfx-37.wav");

}

void ManagerJuego::render(){
	managerVista->render(estadoTick, estadoLogin, username);
}

void ManagerJuego::renderFinJuego(){
	managerVista->renderNivelIntermedio(estadoTick, estadoLogin, username);
}

bool ManagerJuego::terminoJuego() {
    return estadoTick.nuevoNivel == FIN_DE_JUEGO || estadoTick.numeroNivel == FIN_DE_JUEGO;
}

// TODO: che tampoco da
bool ManagerJuego::enJuego() {
    return estadoLogin.estadoLogin == LOGIN_FIN;
}

void ManagerJuego::setInformacionNivel(const InformacionNivel &informacionNivel) {
    ManagerJuego::informacionNivel = informacionNivel;
	managerVista->setInformacionNivel(informacionNivel, estadoTick);
}

void ManagerJuego::setUsername(const std::string &username) {
    ManagerJuego::username = username;
}

void ManagerJuego::verificarJugadoresMuertos(const EstadoTick tick) {
	for (int i = 0; i < MAX_JUGADORES; i++) {
		if (tick.estadosJugadores[i].estaMuerto && !estadoTick.estadosJugadores[i].estaMuerto) {
		    audioPerder->play(100);
			toast->setTexto("NAVE " + std::string(tick.estadosJugadores[i].usuario) + " SIN VIDAS", 5, i + 1);
		}
	}
}

void ManagerJuego::setEstadoTick(const EstadoTick &tick) {
    if (ManagerJuego::estadoTick.numeroNivel == FIN_DE_JUEGO) return;
    verificarJugadoresMuertos(tick);
    ManagerJuego::estadoTick = tick;
	this->setUsername(tick.estadosJugadores[estadoLogin.nroJugador - 1].usuario);

}

void ManagerJuego::setEstadoLogin(const EstadoLogin &estadoLogin) {
    ManagerJuego::estadoLogin = estadoLogin;
}
