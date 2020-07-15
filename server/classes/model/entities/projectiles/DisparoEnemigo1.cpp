//
// Created by camix on 11/7/20.
//

#include "DisparoEnemigo1.h"
#include "../../Enemigo1.h"


DisparoEnemigo1::DisparoEnemigo1(Vector posicion, Vector velocidad) {
    this->posicion = posicion + Vector(ENEMIGO1_ANCHO / 2, ENEMIGO1_ALTO / 2);
    this->velocidad = velocidad.escalar(VELOCIDAD_DISPARO_ENEMIGO1);
    this->vida = new VidaProyectil();
	this->ancho = ANCHO_DISPARO_ENEMIGO1;
	this->alto = ALTO_DISPARO_ENEMIGO1;

    l->debug("Disparo Enemigo01 creado en " + posicion.getVector());
}

EstadoDisparo DisparoEnemigo1::state() {
    EstadoDisparo disparo;
    disparo.posicionX = getPosicion().getX();
    disparo.posicionY = getPosicion().getY();
    disparo.nroJugador = ID_ENEMIGO1;
    disparo.energia = vida->getEnergia();
    disparo.inicio = 0;
    return disparo;
}

float DisparoEnemigo1::getVelocidad() {
    return VELOCIDAD_DISPARO_ENEMIGO1;
}

void DisparoEnemigo1::tick() {
    posicion = posicion + velocidad;
    l->debug("TICK DISPARO ENEMIGO1: " + posicion.getVector());
}

int DisparoEnemigo1::getTipoEntidad() {
    return ENTIDAD_DISPARO_ENEMIGO1;
}


