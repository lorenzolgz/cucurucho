#ifndef CUCURUCHO_ENEMIGO2_H
#define CUCURUCHO_ENEMIGO2_H


#include <string>
#include "../../../commons/utils/Vector.h"
#include "Ticker.h"
#include "EntidadEnemigo.h"

const int ENEMIGO2_ANCHO = 285;
const int ENEMIGO2_ALTO = 147;

class Enemigo2 : public EntidadEnemigo {
public:
    Enemigo2(float x, float y, float velocidadX, std::map<int, Jugador*>* jugadores);

	void tick() override;
	struct EstadoEnemigo state() override;
	int getTipoEntidad() override;
	std::list<Forma> getFormas() override;
	float getVelocidadX() override;
	virtual void setPosicion(Vector nuevaPosicion) override;

private:
    float velocidadX;
};


#endif //CUCURUCHO_ENEMIGO2_H
