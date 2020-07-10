#include "VidaJugadorMortal.h"

#define JUGADOR_ENERGIA_INICIAL 100

VidaJugadorMortal::VidaJugadorMortal() {
	vivir();
}

int VidaJugadorMortal::getEnergiaInicial() {
	return JUGADOR_ENERGIA_INICIAL;
}
