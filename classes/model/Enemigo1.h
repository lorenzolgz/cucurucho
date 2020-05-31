#ifndef CUCURUCHO_ENEMIGO1_H
#define CUCURUCHO_ENEMIGO1_H


#include <SDL_render.h>
#include <string>
#include "../../commons/utils/Vector.h"
#include "../view/Enemigo1Vista.h"
#include "../GeneradorDeTexturas.h"
#include "Ticker.h"
#include "Entidad.h"

const int ENEMIGO1_ANCHO = 66;
const int ENEMIGO1_ALTO = 66;


class Enemigo1 : public Entidad {
public:
	Enemigo1(float x, float y, float velocidadX);

	int getAncho() override;
	int getAlto() override;
	Vector getPosicion() override;
	void tick() override;

private:
    Vector posicion;
	float velocidadX;
    Enemigo1Vista *vista;
};


#endif //CUCURUCHO_ENEMIGO1_H
