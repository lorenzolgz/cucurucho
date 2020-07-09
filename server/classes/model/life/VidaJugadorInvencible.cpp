#include "VidaJugadorInvencible.h"

#define JUGADOR_INVENCIBLE_ENERGIA_INICIAL 100

VidaJugadorInvencible::VidaJugadorInvencible() {
	vivir();
}

int VidaJugadorInvencible::getEnergiaInicial() {
	return JUGADOR_INVENCIBLE_ENERGIA_INICIAL;
}

void VidaJugadorInvencible::procesarColision(const int tipoEntidad) {
	return;
}
