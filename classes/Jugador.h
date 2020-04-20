//
// Created by javier on 10/4/20.
//

#ifndef CPP_SANDBOX_JUGADOR_H
#define CPP_SANDBOX_JUGADOR_H


#include <SDL_render.h>
#include <string>
#include "Vector.h"
#include "GeneradorDeTexturas.h"

const int JUGADOR_ALTO = 48;
const int JUGADOR_ANCHO = 96;
const double JUGADOR_VELOCIDAD_ESCALAR = 4.5;

class Jugador {
public:
    void render();
    void calcularVectorVelocidad(bool arriba, bool abajo, bool izquierda, bool derecha);
    Jugador(GeneradorDeTexturas generadorDeTexturas, SDL_Renderer* gRenderer, int x, int y);

    const Vector &getPosicion() const;

    const Vector getVelocidad() const;

    int getContador() const;

private:
    Vector posicion;
    Vector velocidad;
    double velocidadEscalar;
    int contador;
    int contadorVelocidadY;
    SDL_Texture* textura;
    SDL_Texture* texturaGlow;
    SDL_Renderer* gRenderer;
    //GeneradorDeTexturas generadorDeTexturas;

    void colorGlow();
};


#endif //CPP_SANDBOX_JUGADOR_H
