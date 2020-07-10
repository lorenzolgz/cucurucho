#include "VidaJugador.h"
#include "VidaJugadorMortal.h"
#include "VidaJugadorInvencible.h"
#include "../../../../commons/utils/Log.h"

#define JUGADOR_ENERGIA_INICIAL 100
#define TICKS_COOLDOWN_INVENCIBILIDAD_POR_REVIVIR 100

VidaJugador::VidaJugador() : VidaEntidad(JUGADOR_ENERGIA_INICIAL) {
	this->vidaInterna = new VidaJugadorMortal(JUGADOR_ENERGIA_INICIAL);
	this->invencible = false;
	this->cantidadVidas = 3;
	this->acabaDeMorir = false;
	// Esto es para que no le de invencibilidad cuando recien se crea el jugador.
	this->ticksPostMorir = TICKS_COOLDOWN_INVENCIBILIDAD_POR_REVIVIR + 1;
}

void VidaJugador::procesarColision(const int tipoEntidad) {
	vidaInterna->procesarColision(tipoEntidad);

	if (getEnergia() == 0) {
		if (cantidadVidas == 0) {
			return;
		}
		acabaDeMorir = true;
		cantidadVidas = cantidadVidas - 1;
		ticksPostMorir = 0;

		if (cantidadVidas > 0) {
			vidaInterna = new VidaJugadorInvencible(JUGADOR_ENERGIA_INICIAL);
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

void VidaJugador::tick() {
	if (ticksPostMorir == TICKS_COOLDOWN_INVENCIBILIDAD_POR_REVIVIR) {
		if (!invencible) {
			vidaInterna = new VidaJugadorMortal(JUGADOR_ENERGIA_INICIAL);
		}
	}

	ticksPostMorir = ticksPostMorir + 1;
	acabaDeMorir = false;
}

bool VidaJugador::isAcabaDeMorir() const {
	return acabaDeMorir;
}

bool VidaJugador::esInvencible() {
	return invencible || estaEnCooldownPostMorir();
}

bool VidaJugador::estaEnCooldownPostMorir() {
	return ticksPostMorir < TICKS_COOLDOWN_INVENCIBILIDAD_POR_REVIVIR;
}
