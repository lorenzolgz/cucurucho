//
// Created by camix on 11/7/20.
//

#include "DisparoEnemigo1.h"
#include "../../Enemigo1.h"


DisparoEnemigo1::DisparoEnemigo1(float x, float y) {
    this->posicion = Vector(x + ENEMIGO1_ANCHO, y + ENEMIGO1_ALTO / 3);
    this->velocidad = VELOCIDAD_DISPARO;
    this->vida = new VidaProyectil();
    l->debug("Disparo Enemigo01 creado en " + std::to_string(x) + "," + std::to_string(y));
}

EstadoDisparo DisparoEnemigo1::state() {
    EstadoDisparo disparo;
    disparo.posicionX = getPosicion().getX();
    disparo.posicionY = getPosicion().getY();
    disparo.id = ID_ENEMIGO1;
    return disparo;
}

float DisparoEnemigo1::getVelocidad() {
    return VELOCIDAD_DISPARO;
}

Vector DisparoEnemigo1::getPosicion() {
    return posicion;
}

int DisparoEnemigo1::getAncho() {
    return ANCHO_DISPARO;
}

int DisparoEnemigo1::getAlto() {
    return ALTO_DISPARO;
}

void DisparoEnemigo1::tick() {
    posicion = getPosicion() + Vector(velocidad, 0);
    l->debug("TICK DISPARO ENEMIGO1: " + std::to_string(getPosicion().getX()) + ", " + std::to_string(getPosicion().getX()));
}

int DisparoEnemigo1::getTipoEntidad() {
    return ENTIDAD_DISPARO_ENEMIGO1;
}

std::list<Forma> DisparoEnemigo1::getFormas() {
    std::list<Forma> formas;
    Forma formaSimple = Forma(getPosicion().getX(), getPosicion().getY(), getAncho(), getAlto());
    formas.emplace_back(formaSimple);
    return formas;
}

VidaEntidad *DisparoEnemigo1::getVidaEntidad() {
    return vida;
}

