#ifndef CUCURUCHO_ENEMIGO2_H
#define CUCURUCHO_ENEMIGO2_H

#include <SDL_render.h>
#include <string>
#include "../../../commons/utils/Vector.h"
#include "Ticker.h"
#include "EntidadEnemigo.h"

const int ENEMIGO2_ANCHO = 285;
const int ENEMIGO2_ALTO = 147;

class Enemigo2 : public EntidadEnemigo {
public:
    Enemigo2(float x, float y, float velocidadX);

	int getAncho() override;
	int getAlto() override;
	Vector getPosicion() override;
	void tick() override;
	struct EstadoEnemigo state() override ;

private:
    Vector posicion;
    float velocidadEscalar;
    float velocidadX;

    void recalcularPosicion();
};


#endif //CUCURUCHO_ENEMIGO2_H
