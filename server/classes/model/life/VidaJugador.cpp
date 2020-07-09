#include "VidaJugador.h"

#define PUNTAJE_VIDA_INICIAL 1000

VidaJugador::VidaJugador() {
	this->puntajeVida = PUNTAJE_VIDA_INICIAL;
}

int VidaJugador::getPuntajeVida() {
	return puntajeVida;
}
