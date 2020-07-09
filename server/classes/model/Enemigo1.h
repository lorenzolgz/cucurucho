#ifndef CUCURUCHO_ENEMIGO1_H
#define CUCURUCHO_ENEMIGO1_H


#include <string>
#include "../../../commons/utils/Vector.h"
#include "Ticker.h"
#include "EntidadEnemigo.h"

const int ENEMIGO1_ANCHO = 66;
const int ENEMIGO1_ALTO = 66;


class Enemigo1 : public EntidadEnemigo {
public:
	Enemigo1(float x, float y, float velocidadX);

	Vector getPosicion() override;
	int getAncho() override;
	int getAlto() override;
	void tick() override;
	struct EstadoEnemigo state() override;
	int getTipoEntidad() override;
	std::list<Forma> getFormas() override;
	VidaEntidad* getVidaEntidad() override;

private:
    Vector posicion;
	float velocidadX;
	VidaEntidad* vida;
};


#endif //CUCURUCHO_ENEMIGO1_H
