#include "VidaJugadorMortal.h"

VidaJugadorMortal::VidaJugadorMortal(int energia) : VidaEntidad(energia) {
}

int VidaJugadorMortal::danioColisionEnemigo1() {
	return 10;
}
