#include "VidaEnemigoFinal1.h"

#define ENEMIGO_FINAL1_ENERGIA_INICIAL 1000

VidaEnemigoFinal1::VidaEnemigoFinal1() : VidaEntidad(ENEMIGO_FINAL1_ENERGIA_INICIAL) {
}

int VidaEnemigoFinal1::danioColisionJugador() {
	return 0;
}

int VidaEnemigoFinal1::danioColisionDisparoJugador() {
	return 50;
}
