#include "VidaEnemigo1.h"
#include "../../../../commons/utils/Log.h"
#include "../../../../commons/utils/Constantes.h"

#define ENEMIGO1_ENERGIA_INICIAL 100

VidaEnemigo1::VidaEnemigo1() : VidaEntidad(ENEMIGO1_ENERGIA_INICIAL) {
}

int VidaEnemigo1::danioColisionDisparoJugador() {
	return 50 - HELPERS_ACTIVADOS * 25;
}

