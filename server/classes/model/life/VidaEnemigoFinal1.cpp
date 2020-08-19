#include "VidaEnemigoFinal1.h"
#include "../../../../commons/utils/Constantes.h"

#define ENEMIGO_FINAL1_ENERGIA_INICIAL 1000

VidaEnemigoFinal1::VidaEnemigoFinal1() : VidaEntidad(ENEMIGO_FINAL1_ENERGIA_INICIAL) {
}

int VidaEnemigoFinal1::danioColisionJugador() {
	return 0;
}

int VidaEnemigoFinal1::danioColisionDisparoJugador() {
	return 50 - HELPERS_ACTIVADOS * 30;
}
