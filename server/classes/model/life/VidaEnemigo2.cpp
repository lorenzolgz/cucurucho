#include "VidaEnemigo2.h"

#define ENEMIGO2_ENERGIA_INICIAL 10000;

VidaEnemigo2::VidaEnemigo2() {}

int VidaEnemigo2::getEnergiaInicial() {
	return ENEMIGO2_ENERGIA_INICIAL;
}

int VidaEnemigo2::danioColisionJugador() {
	return 10;
}
