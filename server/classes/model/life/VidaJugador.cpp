#include "VidaJugador.h"

#define JUGADOR_PUNTAJE_VIDA_INICIAL 100

VidaJugador::VidaJugador() {
	vivir();
	this->energia = JUGADOR_PUNTAJE_VIDA_INICIAL;
}

int VidaJugador::getEnergiaInicial() {
	return JUGADOR_PUNTAJE_VIDA_INICIAL;
}

int VidaJugador::danioColisionEnemigo1() {
	return 15;
}

int VidaJugador::danioColisionEnemigo2() {
	return 25;
}
