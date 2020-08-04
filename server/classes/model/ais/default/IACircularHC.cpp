#include <cmath>
#include "IACircularHC.h"
#include "../../../../../commons/utils/Utils.h"

IACircularHC::IACircularHC(EntidadEnemigo *entidadEnemigo, std::map<int, Jugador *> *jugadores, Vector factor, float radio) {
	this->entidadEnemigo = entidadEnemigo;
	this->jugadores = jugadores;
	this->primerTick = true;
	this->ticks = 0;
	this->factor = factor;
	this->radio = radio;
}

IAEnemigo *IACircularHC::tick() {
	if (primerTick) {
		Vector posicionInicial = this->entidadEnemigo->getPosicion();
		this->eje = posicionInicial + (Vector(radio * factor.getX(), 0 * factor.getY()));
		primerTick = false;
	}

	ticks = ticks + 1;

	int gradosAngulo = ticks;
	float posXXX = - (radio * cos_d(gradosAngulo)) * factor.getX();
	float posYYY = - (radio * sin_d(gradosAngulo)) * factor.getY();
	entidadEnemigo->setPosicion(eje + Vector(posXXX, posYYY));

	return this;
}
