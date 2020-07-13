//
// Created by camix on 12/7/20.
//

#include "DisparoEnemigo2.h"
#include "../../Enemigo2.h"

DisparoEnemigo2::DisparoEnemigo2(float x, float y) {
    this->posicion = Vector(x + ENEMIGO2_ANCHO, y + ENEMIGO2_ALTO / 3);
    this->velocidad = VELOCIDAD_DISPARO_ENEMIGO2;
    this->vida = new VidaProyectil();
    l->debug("Disparo Enemigo01 creado en " + std::to_string(x) + "," + std::to_string(y));
}

EstadoDisparo DisparoEnemigo2::state() {
    EstadoDisparo disparo;
    disparo.posicionX = getPosicion().getX();
    disparo.posicionY = getPosicion().getY();
    disparo.id = ID_ENEMIGO2;
    return disparo;
}

float DisparoEnemigo2::getVelocidad() {
    return VELOCIDAD_DISPARO_ENEMIGO2;
}

Vector DisparoEnemigo2::getPosicion() {
    return posicion;
}

int DisparoEnemigo2::getAncho() {
    return ANCHO_DISPARO_ENEMIGO2;
}

int DisparoEnemigo2::getAlto() {
    return ALTO_DISPARO_ENEMIGO2;
}

void DisparoEnemigo2::tick() {
    posicion = getPosicion() + Vector(velocidad, 0);
    l->debug("TICK DISPARO ENEMIGO1: " + std::to_string(getPosicion().getX()) + ", " + std::to_string(getPosicion().getX()));
}

int DisparoEnemigo2::getTipoEntidad() {
    return ENTIDAD_DISPARO_ENEMIGO1;
}

std::list<Forma> DisparoEnemigo2::getFormas() {
    std::list<Forma> formas;
    Forma formaSimple = Forma(getPosicion().getX(), getPosicion().getY(), getAncho(), getAlto());
    formas.emplace_back(formaSimple);
    return formas;
}

VidaEntidad *DisparoEnemigo2::getVidaEntidad() {
    return vida;
}

