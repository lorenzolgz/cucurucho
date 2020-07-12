//
// Created by lorenzo on 7/9/20.
//

#include "Disparo.h"
#include "../../../../../commons/utils/Log.h"
#include "../../life/VidaProyectil.h"
#include "../../Jugador.h"
#include <iostream>

#define ANCHO_DISPARO 96
#define ALTO_DISPARO 24
#define VELOCIDAD_DISPARO 13

Disparo::Disparo(float x, float y, int nroJugador) {
	this->posicion = Vector(x + JUGADOR_ANCHO * 1 / 3, y + JUGADOR_ALTO / 5);
    this->velocidad = VELOCIDAD_DISPARO;
    this->nroJugador = nroJugador;
    this->vida = new VidaProyectil();
    l->debug("Disparo creado en " + std::to_string(x) + "," + std::to_string(y));
}

void Disparo::tick() {
	posicion = getPosicion() + Vector(velocidad, 0);
    l->debug("TICK DISPARO: " + std::to_string(getPosicion().getX()) + ", " + std::to_string(getPosicion().getX()));
}

Vector Disparo::getPosicion() {
	return posicion;
}

int Disparo::getAncho() {
    return ANCHO_DISPARO;
}

int Disparo::getAlto() {
    return ALTO_DISPARO;
}

float Disparo::getVelocidad() {
    return this->velocidad;
}

// Estado que se le envia al cliente (unicamente con la info que necesita)
EstadoDisparo Disparo::state() {
    EstadoDisparo disparo;
    disparo.posicionX = getPosicion().getX();
    disparo.posicionY = getPosicion().getY();
    disparo.id = nroJugador;
    disparo.energia = vida->getEnergia();
    return disparo;
}

int Disparo::getTipoEntidad() {
	return ENTIDAD_DISPARO_JUGADOR;
}

std::list<Forma> Disparo::getFormas() {
	std::list<Forma> formas;
	Forma formaSimple = Forma(getPosicion().getX(), getPosicion().getY(), getAncho(), getAlto());
	formas.emplace_back(formaSimple);
	return formas;
}

VidaEntidad *Disparo::getVidaEntidad() {
	return vida;
}
