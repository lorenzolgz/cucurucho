//
// Created by lorenzo on 7/9/20.
//

#include "Disparo.h"
#include "../../../../../commons/utils/Log.h"
#include "../../life/VidaProyectil.h"
#include <iostream>

Disparo::Disparo(float x, float y, Jugador* jugador) {
	this->posicion = Vector(x + JUGADOR_ANCHO * 1 / 3, y + JUGADOR_ALTO / 5);
	this->ancho = ANCHO_DISPARO_JUGADOR;
	this->alto = ALTO_DISPARO_JUGADOR;
	this->velocidad = Vector(VELOCIDAD_DISPARO_JUGADOR, 0);
    this->jugador = jugador;
    this->vida = new VidaProyectil();
    this->inicio = this->posicion;
    this->helper = 0;
    l->debug("Disparo creado en " + this->posicion.getVector());
}

Disparo::Disparo(Vector posicion, Vector velocidad, int ancho, int alto, Jugador* jugador) {
	this->posicion = posicion;
	this->velocidad = velocidad;
	this->ancho = ancho;
	this->alto = alto;
	this->jugador = jugador;
	this->vida = new VidaProyectil();
	this->inicio = this->posicion;
	this->helper = 1;
	l->debug("Disparo creado en " + this->posicion.getVector());
}

void Disparo::tick() {
	posicion = getPosicion() + velocidad;
    l->debug("TICK DISPARO: " + std::to_string(getPosicion().getX()) + ", " + std::to_string(getPosicion().getX()));
}

Vector Disparo::getVelocidad() {
    return this->velocidad;
}

// Estado que se le envia al cliente (unicamente con la info que necesita)
EstadoDisparo Disparo::state() {
    EstadoDisparo disparo;
    disparo.posicionX = getPosicion().getX();
    disparo.posicionY = getPosicion().getY();
    disparo.nroJugador = jugador->getNroJugador() + this->helper * 8 + ((int) getVelocidad().arg()) * 16;
    disparo.energia = vida->getEnergia();
    disparo.inicio = inicio.getX();
    return disparo;
}

int Disparo::getTipoEntidad() {
	return ENTIDAD_DISPARO_JUGADOR;
}

void Disparo::matoEntidad(int tipoEntidad) {
	jugador->sumarPuntosPorDestruirA(tipoEntidad);
}
