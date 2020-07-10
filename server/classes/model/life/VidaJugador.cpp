#include "VidaJugador.h"
#include "VidaJugadorMortal.h"
#include "VidaJugadorInvencible.h"
#include "../../../../commons/utils/Log.h"

#define JUGADOR_ENERGIA_INICIAL 100
#define TICKS_COOLDOWN_INVENCIBILIDAD_POR_NACER 100
#define TICKS_COOLDOWN_INMOVIL_POST_NACER 30

VidaJugador::VidaJugador() : VidaEntidad(JUGADOR_ENERGIA_INICIAL) {
	this->vidaInterna = new VidaJugadorMortal(JUGADOR_ENERGIA_INICIAL);
	this->invencible = false;
	this->cantidadVidas = 3;
	this->acabaDePerderUnaVida = false;
	// Esto es para que no le de invencibilidad cuando recien se crea el jugador.
	this->ticksPostNacer = 0;
}

void VidaJugador::procesarColision(const int tipoEntidad) {
	vidaInterna->procesarColision(tipoEntidad);

	if (getEnergia() == 0) {
		if (cantidadVidas == 0) {
			return;
		} else {
			acabaDePerderUnaVida = true;
			cantidadVidas = cantidadVidas - 1;
			ticksPostNacer = 0;

			if (cantidadVidas == 0) {
				l->info("Murio un jugador.");
			} else {
				vidaInterna = new VidaJugadorInvencible(JUGADOR_ENERGIA_INICIAL);
			}
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
	if (ticksPostNacer == TICKS_COOLDOWN_INVENCIBILIDAD_POR_NACER) {
		if (!invencible) {
			vidaInterna = new VidaJugadorMortal(getEnergia());
		}
	}

	ticksPostNacer = ticksPostNacer + 1;
	acabaDePerderUnaVida = false;
}

bool VidaJugador::isAcabaDePerderUnaVida() const {
	return acabaDePerderUnaVida;
}

bool VidaJugador::esInvencible() {
	return invencible || estaEnCooldownInvenciblePostNacer();
}

bool VidaJugador::estaEnCooldownInvenciblePostNacer() {
	return ticksPostNacer < TICKS_COOLDOWN_INVENCIBILIDAD_POR_NACER;
}

bool VidaJugador::estaEnCooldownInmovilPostNacer() {
	return ticksPostNacer < TICKS_COOLDOWN_INMOVIL_POST_NACER;
}

void VidaJugador::nacer() {
	ticksPostNacer = 0;
}

bool VidaJugador::noTieneMasVidas() {
	return cantidadVidas == 0;
}
