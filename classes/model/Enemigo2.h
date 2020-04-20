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
#include "Ticker.h"

const int ENEMIGO2_ANCHO = 285;
const int ENEMIGO2_ALTO = 147;

class Enemigo2 : public Ticker {
public:
    Enemigo2(float x, float y);
	void tick() override;

private:
    Vector posicion;
    Vector velocidad;
    float velocidadEscalar;
    bool velocidadX;

    Enemigo2Vista *vista;

    void recalcularPosicion();
};


#endif //CUCURUCHO_ENEMIGO2_H
