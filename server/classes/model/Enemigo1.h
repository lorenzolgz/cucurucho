#ifndef CUCURUCHO_ENEMIGO1_H
#define CUCURUCHO_ENEMIGO1_H


#include <string>
#include "../../../commons/utils/Vector.h"
#include "Ticker.h"
#include "EntidadEnemigo.h"
#include "Jugador.h"

const int ENEMIGO1_ANCHO = 66;
const int ENEMIGO1_ALTO = 66;


class Enemigo1 : public EntidadEnemigo {
public:
	Enemigo1(float x, float y, float velocidadX, std::map<int, Jugador*>* jugadores);

	void tick() override;
	struct EstadoEnemigo state() override;
	int getTipoEntidad() override;
	float getVelocidadX() override ;
	virtual void setPosicion(Vector nuevaPosicion) override;

private:
	float velocidadX;
};


#endif //CUCURUCHO_ENEMIGO1_H
