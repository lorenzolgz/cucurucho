#include "IAEstatico.h"
#include "IACircular.h"

IAEstatico::IAEstatico(EntidadEnemigo *entidadEnemigo, std::map<int, Jugador *> *jugadores, int maxTicks, IAEnemigo* next) {
	this->entidadEnemigo = entidadEnemigo;
	this->jugadores = jugadores;
	this->ticks = 0;
	this->maxTicks = maxTicks;
	this->next = next;
}

IAEnemigo *IAEstatico::tick() {
	ticks = ticks + 1;
	if (ticks == maxTicks) {
		return next;
	}

	return this;
}
