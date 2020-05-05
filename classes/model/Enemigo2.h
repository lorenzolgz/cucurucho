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
#include "Entidad.h"

const int ENEMIGO2_ANCHO = 285;
const int ENEMIGO2_ALTO = 147;

class Enemigo2 : public Entidad {
public:
    Enemigo2(float x, float y, float velocidadX);

	int getAncho() override;
	int getAlto() override;
	Vector getPosicion() override;
	void tick() override;

private:
    Vector posicion;
    float velocidadEscalar;
    float velocidadX;
    Enemigo2Vista *vista;

    void recalcularPosicion();
};


#endif //CUCURUCHO_ENEMIGO2_H
