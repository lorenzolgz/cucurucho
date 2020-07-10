#include "VidaJugador.h"
#include "VidaJugadorMortal.h"
#include "VidaJugadorInvencible.h"

#define JUGADOR_ENERGIA_INICIAL 100

VidaJugador::VidaJugador() : VidaEntidad(JUGADOR_ENERGIA_INICIAL) {
	this->vidaInterna = new VidaJugadorMortal(JUGADOR_ENERGIA_INICIAL);
	this->invencible = false;
	this->cantidadVidas = 3;
}

void VidaJugador::procesarColision(const int tipoEntidad) {
	vidaInterna->procesarColision(tipoEntidad);

	if (getEnergia() == 0) {
		if (cantidadVidas == 0) {
			return;
		}
		cantidadVidas = cantidadVidas - 1;
		if (invencible) {
			vidaInterna = new VidaJugadorInvencible(JUGADOR_ENERGIA_INICIAL);
		} else {
			vidaInterna = new VidaJugadorMortal(JUGADOR_ENERGIA_INICIAL);
		}
	}
}

int VidaJugador::getEnergia() {
	return vidaInterna->getEnergia();
}

void VidaJugador::cambiarInvencible(bool invencible) {
	if (this->invencible == invencible) {
		return;
	}

	if (invencible) {
		vidaInterna = new VidaJugadorInvencible(vidaInterna->getEnergia());
	} else {
		vidaInterna = new VidaJugadorMortal(vidaInterna->getEnergia());
	}

	this->invencible = invencible;
}

int VidaJugador::getCantidadVidas() {
	return cantidadVidas;
}
