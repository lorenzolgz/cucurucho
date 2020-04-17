//
// Created by camix on 15/4/20.
//

#ifndef CUCURUCHO_ENEMIGO2_H
#define CUCURUCHO_ENEMIGO2_H

#include <SDL_render.h>
#include <string>
#include "Vector.h"

class Enemigo2 {
public:
    void render();
    Enemigo2(SDL_Renderer* gRenderer, float x, float y);

private:
    float posicionx;
    float posiciony;
    Vector velocidad;
    float velocidadEscalar;
    bool VelocidadX;
    SDL_Texture* textura;
    SDL_Texture* texturaGlow;
    SDL_Renderer* gRenderer;


    SDL_Rect calcularMovimiento(float *x, float y, int width, int height);
};


#endif //CUCURUCHO_ENEMIGO2_H
