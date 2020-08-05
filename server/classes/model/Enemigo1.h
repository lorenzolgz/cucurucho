#ifndef CUCURUCHO_ENEMIGO1_H
#define CUCURUCHO_ENEMIGO1_H


#include <string>
#include "../../../commons/utils/Vector.h"
#include "Ticker.h"
#include "EntidadEnemigo.h"
#include "Jugador.h"
#include "entities/projectiles/DisparoEnemigo1.h"

const int ENEMIGO1_ANCHO = 66;
const int ENEMIGO1_ALTO = 66;
const int TICKS_COOLDOWN_DISPARO_ENEMIGO1 = 280;


class Enemigo1 : public EntidadEnemigo {
public:
	Enemigo1(float x, float y, float velocidadX, std::map<int, Jugador*>* jugadores, CampoMovil* campo);
	~Enemigo1();

	void tick() override;
	struct EstadoEnemigo state() override;
	int getTipoEntidad() override;
	float getVelocidadX() override ;
	virtual void setPosicion(Vector nuevaPosicion) override;
    virtual void disparar(Vector vector) override;

private:
	float velocidadX;
    int ticksHastaDisparo;
    Vector ultimaPosicion;
    int ultimoAngulo;
    CampoMovil* campo;
};


#endif //CUCURUCHO_ENEMIGO1_H
