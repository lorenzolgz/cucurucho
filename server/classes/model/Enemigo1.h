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
const int TICKS_COOLDOWN_DISPARO_ENEMIGO1 = 60;


class Enemigo1 : public EntidadEnemigo {
public:
	Enemigo1(float y, float velocidadX, std::map<int, Jugador*>* jugadores, CampoMovil* campo);

	Vector getPosicion() override;
	int getAncho() override;
	int getAlto() override;
	void tick() override;
	struct EstadoEnemigo state() override;
	int getTipoEntidad() override;
	std::list<Forma> getFormas() override;
	VidaEntidad* getVidaEntidad() override;
	float getVelocidadX() override ;
	virtual void setPosicion(Vector nuevaPosicion) override;
    virtual void disparar() override;

private:
    Vector posicion;
	float velocidadX;
	VidaEntidad* vida;
    int ticksHastaDisparo;
    CampoMovil* campo;


};


#endif //CUCURUCHO_ENEMIGO1_H
