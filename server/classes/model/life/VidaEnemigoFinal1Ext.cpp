//
// Created by javier on 19/7/20.
//

#include "VidaEnemigoFinal1Ext.h"

#define ENEMIGO_FINAL1_EXT_ENERGIA_INICIAL 250


VidaEnemigoFinal1Ext::VidaEnemigoFinal1Ext() : VidaEntidad(ENEMIGO_FINAL1_EXT_ENERGIA_INICIAL) {
}

int VidaEnemigoFinal1Ext::danioColisionJugador() {
	return DANIO_TOTAL;
}

int VidaEnemigoFinal1Ext::danioColisionDisparoJugador() {
	return 50;
}
