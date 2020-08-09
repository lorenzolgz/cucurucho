//
// Created by javier on 19/7/20.
//

#ifndef CUCURUCHO_ENEMIGOFINAL1EXT_H
#define CUCURUCHO_ENEMIGOFINAL1EXT_H


#include "EnemigoFinal1.h"

const int ENEMIGO_FINAL1_EXT_ANCHO = 42;
const int ENEMIGO_FINAL1_EXT_ALTO = 42;

class EnemigoFinal1Ext : public EntidadEnemigo {
public:
	EnemigoFinal1Ext(std::map<int, Jugador *> *jugadores, CampoMovil* campo, EnemigoFinal1 *padre,
			Vector posRelativa, Vector inferior, Vector superior);
	virtual ~EnemigoFinal1Ext();

	EstadoEnemigo state() override;
	float getVelocidadX() override;
	void setPosicion(Vector nuevaPosicion) override;
	void tick() override;
	std::list<Forma> getFormas() override;
	int getTipoEntidad() override;
	void disparar(Vector vector) override;

private:
	float velocidadX;
	EnemigoFinal1* padre;
	int ticksHastaDisparo;
	CampoMovil *campo;
	std::deque<Vector> posiciones;
};


#endif //CUCURUCHO_ENEMIGOFINAL1EXT_H
