#include "VidaJugador.h"

#define JUGADOR_ENERGIA_INICIAL 100

VidaJugador::VidaJugador() {
	vivir();
}

int VidaJugador::getEnergiaInicial() {
	return JUGADOR_ENERGIA_INICIAL;
}

int VidaJugador::danioColisionEnemigo1() {
	return 15;
}

int VidaJugador::danioColisionEnemigo2() {
	return 25;
}
