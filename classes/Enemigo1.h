//
// Created by camix on 16/4/20.
//

#ifndef CUCURUCHO_ENEMIGO1_H
#define CUCURUCHO_ENEMIGO1_H
#include <SDL_render.h>
#include <string>
#include "Vector.h"

const int ENEMIGO1_ANCHO = 66;
const int ENEMIGO1_ALTO = 66;


class Enemigo1 {
public:
    void render();
    Enemigo1(SDL_Renderer* gRenderer, float x, float y);

private:
    Vector posicion;
    float velocidadEscalar;
    int VelocidadX;
    SDL_Texture* textura;
    SDL_Texture* texturaGlow;
    SDL_Renderer* gRenderer;


    SDL_Rect calcularMovimiento(int width, int height);
};


#endif //CUCURUCHO_ENEMIGO1_H
