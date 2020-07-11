#include "IAHorizontal.h"
#include "../../../../../commons/utils/Constantes.h"
#include "IAEstatico.h"
#include "IACircular.h"

IAHorizontal::IAHorizontal(EntidadEnemigo* entidadEnemigo, std::map<int, Jugador*>* jugadores, float paddingIzquierdo, IAEnemigo* next) {
	this->entidadEnemigo = entidadEnemigo;
	this->jugadores = jugadores;
	this->paddingIzquierdo = paddingIzquierdo;
	this->next = next;
}

IAEnemigo* IAHorizontal::tick() {
	if (entidadEnemigo->getPosicion().getX() < PANTALLA_ANCHO - paddingIzquierdo -entidadEnemigo->getAncho()) {
		return next;
	}
	Vector nuevaPosicion = entidadEnemigo->getPosicion() - Vector(entidadEnemigo->getVelocidadX(), 0);
	entidadEnemigo->setPosicion(nuevaPosicion);

	return this;
}