//
// Created by camix on 12/7/20.
//

#include "DisparoEnemigo2.h"
#include "../../Enemigo2.h"

DisparoEnemigo2::DisparoEnemigo2(Vector posicion, Vector direccion) {
    this->posicion = posicion + Vector(ENEMIGO2_ANCHO / 2, ENEMIGO2_ALTO / 2);
    this->velocidad = direccion.escalar(VELOCIDAD_DISPARO_ENEMIGO2);
    this->vida = new VidaProyectil();
    this->ancho = ANCHO_DISPARO_ENEMIGO2;
    this->alto = ALTO_DISPARO_ENEMIGO2;
    l->debug("Disparo Enemigo01 creado en " + posicion.getVector());
}

EstadoDisparo DisparoEnemigo2::state() {
    EstadoDisparo disparo;
    disparo.posicionX = getPosicion().getX();
    disparo.posicionY = getPosicion().getY();
    disparo.nroJugador = ID_ENEMIGO2;
	disparo.energia = vida->getEnergia();
	disparo.inicio = 0;
    return disparo;
}

float DisparoEnemigo2::getVelocidad() {
    return VELOCIDAD_DISPARO_ENEMIGO2;
}

void DisparoEnemigo2::tick() {
    posicion = posicion + velocidad;
    l->debug("TICK DISPARO ENEMIGO1: " + posicion.getVector());
}

int DisparoEnemigo2::getTipoEntidad() {
    return ENTIDAD_DISPARO_ENEMIGO2;
}
