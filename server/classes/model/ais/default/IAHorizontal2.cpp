#include "IAHorizontal2.h"
#include "../../../../../commons/utils/Constantes.h"

IAHorizontal2::IAHorizontal2(EntidadEnemigo* entidadEnemigo, std::map<int, Jugador*>* jugadores, bool sentidoXPositivo, float posXFinal, IAEnemigo* next) {
	this->entidadEnemigo = entidadEnemigo;
	this->jugadores = jugadores;
	this->ticks = 0;
	this->posXFinal = posXFinal;
	this->sentidoXPositivo = sentidoXPositivo;
	this->next = next;
}

IAEnemigo* IAHorizontal2::tick() {
	if (entidadEnemigo->getPosicion().getX() >= posXFinal) {
		l->error("!!!! pasaje");
		return next;
	}

	ticks = ticks + 1;

	int factorModificadorSentido = sentidoXPositivo ? 1 : -1;
	Vector nuevaPosicion = entidadEnemigo->getPosicion() + Vector(factorModificadorSentido * std::abs(entidadEnemigo->getVelocidadX()), 0);
	l->error("!!!! posicion " + std::to_string(nuevaPosicion.getX()) + " - " + std::to_string(nuevaPosicion.getY()));
	entidadEnemigo->setPosicion(nuevaPosicion);

	return this;
}
