#ifndef CUCURUCHO_ENEMIGO2_H
#define CUCURUCHO_ENEMIGO2_H


#include <string>
#include "../../../commons/utils/Vector.h"
#include "Ticker.h"
#include "EntidadEnemigo.h"

const int ENEMIGO2_ANCHO = 285;
const int ENEMIGO2_ALTO = 147;
#define TICKS_COOLDOWN_DISPARO_ENEMIGO2 60

class Enemigo2 : public EntidadEnemigo {
public:
    Enemigo2(float x, float y, float velocidadX, std::map<int, Jugador*>* jugadores, CampoMovil* campo);

	void tick() override;
	struct EstadoEnemigo state() override;
	int getTipoEntidad() override;
	std::list<Forma> getFormas() override;
	float getVelocidadX() override;
	virtual void setPosicion(Vector nuevaPosicion) override;
    virtual void disparar(Vector vector) override;

private:
    float velocidadX;
    int ticksHastaDisparo;
    CampoMovil* campo;
};


#endif //CUCURUCHO_ENEMIGO2_H
