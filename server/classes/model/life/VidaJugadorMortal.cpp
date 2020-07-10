#include "VidaJugadorMortal.h"

VidaJugadorMortal::VidaJugadorMortal(int energia) : VidaEntidad(energia) {
}

int VidaJugadorMortal::danioColisionEnemigo1() {
	// TODO sacar esta funcion, lo puse asi para probar mientras no hay disparos!!!!
	return 35;
}
