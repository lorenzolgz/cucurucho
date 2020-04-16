//
// Created by javier on 12/4/20.
//

#ifndef CUCURUCHO_HELPER_H
#define CUCURUCHO_HELPER_H


#include <array>
#include <deque>
#include "Vector.h"
#include "Jugador.h"

class Helper {
public:
    Helper(SDL_Renderer * gRenderer, Jugador* jugador, Vector posRelativa);
    void render();
private:
    Vector posicion;
    Vector velocidad;
    Vector posRelativa;
    Jugador* jugador;
    SDL_Renderer* gRenderer;
    SDL_Texture* textura;
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
