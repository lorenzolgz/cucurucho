#include "VidaJugadorMortal.h"

#define JUGADOR_ENERGIA_INICIAL 100

VidaJugadorMortal::VidaJugadorMortal() {
	vivir();
}

int VidaJugadorMortal::getEnergiaInicial() {
	return JUGADOR_ENERGIA_INICIAL;
}

int VidaJugadorMortal::danioColisionEnemigo1() {
	return 15;
}

int VidaJugadorMortal::danioColisionEnemigo2() {
	return 0;
}
