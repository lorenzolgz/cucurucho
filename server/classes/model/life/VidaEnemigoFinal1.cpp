#include "VidaEnemigoFinal1.h"

// !!!!! poner 1000
#define ENEMIGO_FINAL1_ENERGIA_INICIAL 300

VidaEnemigoFinal1::VidaEnemigoFinal1() : VidaEntidad(ENEMIGO_FINAL1_ENERGIA_INICIAL) {
}

int VidaEnemigoFinal1::danioColisionDisparoJugador() {
	return 50;
}
