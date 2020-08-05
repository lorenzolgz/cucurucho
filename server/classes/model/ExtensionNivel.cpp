#include "ExtensionNivel.h"

ExtensionNivel::ExtensionNivel(CampoMovil* campo, std::map<int, Jugador*>* jugadores) {
	this->iniciado = false;
	this->ticksPostMuerteEnemigoFinal = 0;
	this->maxTicksPostMuerteEnemigoFinal = 300;
	this->campo = campo;
	this->enemigoFinal = new EnemigoFinal1(campo->getAncho() + 200, 125, campo->getVelocidadX(), jugadores, campo);
}

void ExtensionNivel::iniciar() {
	iniciado = true;
	campo->agregarEntidadEnemigo(enemigoFinal);
	for (EntidadEnemigo* enemigo : enemigoFinal->getExtensiones()) {
		campo->agregarEntidadEnemigo(enemigo);
	}
}

bool ExtensionNivel::termino() {
	return ticksPostMuerteEnemigoFinal == maxTicksPostMuerteEnemigoFinal;
}

bool ExtensionNivel::isIniciado() {
	return iniciado;
}

void ExtensionNivel::tick() {
	if (enemigoFinal->getVidaEntidad()->estaMuerto()) {
		ticksPostMuerteEnemigoFinal = ticksPostMuerteEnemigoFinal + 1;
	}
}
