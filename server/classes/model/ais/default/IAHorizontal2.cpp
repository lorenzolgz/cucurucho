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
	if ((sentidoXPositivo && entidadEnemigo->getPosicion().getX() >= posXFinal) ||
			!sentidoXPositivo && entidadEnemigo->getPosicion().getX() <= posXFinal) {
		next->inicializar();
		return next;
	}

	ticks = ticks + 1;

	int factorModificadorSentido = sentidoXPositivo ? 1 : -1;
	Vector nuevaPosicion = entidadEnemigo->getPosicion() + Vector(factorModificadorSentido * std::abs(entidadEnemigo->getVelocidadX()), 0);
	entidadEnemigo->setPosicion(nuevaPosicion);

	return this;
}
