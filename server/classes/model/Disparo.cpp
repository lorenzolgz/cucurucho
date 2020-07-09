//
// Created by lorenzo on 7/9/20.
//

#include "Disparo.h"
#include "../../../commons/utils/Log.h"
#include <iostream>

Disparo::Disparo(float x, float y, int id, int ancho, int alto, float velocidad) {
    this->x = x;
    this->y = y;
    this->id = id;
    this->ancho = ancho;
    this->alto = alto;
    this->velocidad = velocidad;
    l->debug("Disparo creado en " + std::to_string(x) + "," + std::to_string(y));
}

void Disparo::tick() {
    this->x += velocidad;
    l->debug("TICK DISPARO: " + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(id));
}

float Disparo::getX() {
    return this->x;
}

float Disparo::getY() {
    return this->y;
}

int Disparo::getId() {
    return this->id;
}

int Disparo::getAncho() {
    return this->ancho;
}

int Disparo::getAlto() {
    return this->alto;
}

float Disparo::getVelocidad() {
    return this->velocidad;
}

// Estado que se le envia al cliente (unicamente con la info que necesita)
EstadoDisparo Disparo::state() {
    EstadoDisparo disparo;
    disparo.posicionX = x;
    disparo.posicionY = y;
    disparo.id = id;
    return disparo;
}
