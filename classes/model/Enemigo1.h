#ifndef CUCURUCHO_ENEMIGO1_H
#define CUCURUCHO_ENEMIGO1_H


#include <SDL_render.h>
#include <string>
#include "../Vector.h"
#include "../view/Enemigo1Vista.h"
#include "../GeneradorDeTexturas.h"

const int ENEMIGO1_ANCHO = 66;
const int ENEMIGO1_ALTO = 66;


class Enemigo1 {
public:
	Enemigo1(SDL_Renderer* gRenderer, float x, float y);
	void render();

private:
    Vector posicion;
    int velocidadX;
    Enemigo1Vista *vista;
};


#endif //CUCURUCHO_ENEMIGO1_H
