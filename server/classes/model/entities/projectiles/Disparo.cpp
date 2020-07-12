//
// Created by lorenzo on 7/9/20.
//

#include "Disparo.h"
#include "../../../../../commons/utils/Log.h"
#include "../../life/VidaProyectil.h"
#include <iostream>

#define ANCHO_DISPARO_JUGADOR 96
#define ALTO_DISPARO_JUGADOR 24
#define VELOCIDAD_DISPARO_JUGADOR 14

Disparo::Disparo(float x, float y, Jugador* jugador) {
	this->posicion = Vector(x + JUGADOR_ANCHO * 1 / 3, y + JUGADOR_ALTO / 5);
	this->ancho = ANCHO_DISPARO_JUGADOR;
	this->alto = ALTO_DISPARO_JUGADOR;
	this->velocidad = VELOCIDAD_DISPARO_JUGADOR;
    this->jugador = jugador;
    this->vida = new VidaProyectil();
    l->debug("Disparo creado en " + std::to_string(x) + "," + std::to_string(y));
}

void Disparo::tick() {
	posicion = getPosicion() + Vector(velocidad, 0);
    l->debug("TICK DISPARO: " + std::to_string(getPosicion().getX()) + ", " + std::to_string(getPosicion().getX()));
}

float Disparo::getVelocidad() {
    return this->velocidad;
}

// Estado que se le envia al cliente (unicamente con la info que necesita)
EstadoDisparo Disparo::state() {
    EstadoDisparo disparo;
    disparo.posicionX = getPosicion().getX();
    disparo.posicionY = getPosicion().getY();
    disparo.nroJugador = jugador->getNroJugador();
    disparo.energia = vida->getEnergia();
    return disparo;
}

int Disparo::getTipoEntidad() {
	return ENTIDAD_DISPARO_JUGADOR;
}

void Disparo::matoEntidad(int tipoEntidad) {
	jugador->sumarPuntosPorDestruirA(tipoEntidad);
}
