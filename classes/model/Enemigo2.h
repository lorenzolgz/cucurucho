//
// Created by camix on 15/4/20.
//

#ifndef CUCURUCHO_ENEMIGO2_H
#define CUCURUCHO_ENEMIGO2_H

#include <SDL_render.h>
#include <string>
#include "../Vector.h"
#include "../view/Enemigo2Vista.h"
#include "../GeneradorDeTexturas.h"

const int ENEMIGO2_ANCHO = 285;
const int ENEMIGO2_ALTO = 147;

class Enemigo2 {
public:
    void render();
    Enemigo2(SDL_Renderer* gRenderer, float x, float y);

private:
    Vector posicion;
    Vector velocidad;
    float velocidadEscalar;
    bool velocidadX;

    Enemigo2Vista *vista;

    void recalcularPosicion();
};


#endif //CUCURUCHO_ENEMIGO2_H
