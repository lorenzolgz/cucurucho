#include "VidaEntidad.h"
#include "../entities/Entidad.h"

void VidaEntidad::vivir() {
	energia = getEnergiaInicial();
}

int VidaEntidad::getEnergia() {
	return energia;
}

void VidaEntidad::procesarColision(const int tipoEntidad) {
	int danio = calcularDanioPorColision(tipoEntidad);

	if (danio == DANIO_TOTAL) {
		energia = 0;
	} else {
		energia = energia - danio;
		if (energia < 0) {
			energia = 0;
		}
	}
}

int VidaEntidad::calcularDanioPorColision(const int tipoEntidad) {
	switch (tipoEntidad) {
		case ENTIDAD_JUGADOR:
			return danioColisionJugador();
		case ENTIDAD_ENEMIGO1:
			return danioColisionEnemigo1();
		case ENTIDAD_ENEMIGO2:
			return danioColisionEnemigo2();
		case ENTIDAD_DISPARO_JUGADOR:
			return danioColisionDisparoJugador();
		default:
			return DANIO_TOTAL;
	}
}

int VidaEntidad::danioColisionJugador() {
	return DANIO_TOTAL;
}

int VidaEntidad::danioColisionEnemigo1() {
	return DANIO_TOTAL;
}

int VidaEntidad::danioColisionEnemigo2() {
	return DANIO_TOTAL;
}

int VidaEntidad::danioColisionDisparoJugador() {
	return DANIO_TOTAL;
}
