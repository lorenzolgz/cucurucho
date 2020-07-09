#include "VidaEnemigo1.h"

#define ENEMIGO1_ENERGIA_INICIAL 100

VidaEnemigo1::VidaEnemigo1() {}

int VidaEnemigo1::getEnergiaInicial() {
	return ENEMIGO1_ENERGIA_INICIAL;
}

int VidaEnemigo1::danioColisionJugador() {
	return VidaEntidad::danioColisionJugador();
}

