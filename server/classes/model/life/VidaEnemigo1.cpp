#include "VidaEnemigo1.h"
#include "../../../../commons/utils/Log.h"

#define ENEMIGO1_ENERGIA_INICIAL 100

VidaEnemigo1::VidaEnemigo1() {
	vivir();
}

int VidaEnemigo1::getEnergiaInicial() {
	return ENEMIGO1_ENERGIA_INICIAL;
}

int VidaEnemigo1::danioColisionDisparoJugador() {
	return 50;
}
