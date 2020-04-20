//
// Created by javier on 12/4/20.
//

#ifndef CUCURUCHO_HELPER_H
#define CUCURUCHO_HELPER_H


#include <array>
#include <deque>
#include "Vector.h"
#include "Jugador.h"
#include "GeneradorDeTexturas.h"

const int HELPER_RADIO_BALL = 24;
const int HELPER_DISTANCIA = 27;

const double HELPER_VEL_ANGULAR = 15;
const double HELPER_ACELERACION = 0.2;

const int HELPER_ALTO = 48;
const int HELPER_ANCHO = 48;

class Helper {
public:
    Helper(GeneradorDeTexturas generadorDeTexturas, SDL_Renderer * gRenderer, Jugador* jugador, Vector posRelativa);
    void render();
private:
    Vector posicion;
    Vector velocidad;
    Vector posRelativa;
    Jugador* jugador;
    SDL_Renderer* gRenderer;
    SDL_Texture* textura;
    //GeneradorDeTexturas generadorDeTexturas;
    std::deque<Vector> recorrido;
    double velAngular;
    double angulo;
    double aceleracion;

    void renderGlow();

    void renderBall();
    void renderHelper();

    void calcularAngulo();

    void calcularVelocidad();
};


#endif //CUCURUCHO_HELPER_H
