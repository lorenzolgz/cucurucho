#include "ExtensionNivel.h"

ExtensionNivel::ExtensionNivel(CampoMovil* campo, std::map<int, Jugador*>* jugadores) {
	this->iniciado = false;
	this->ticksPostMuerteEnemigoFinal = 0;
	this->maxTicksPostMuerteEnemigoFinal = 300;
	this->campo = campo;
	this->enemigoFinal = new EnemigoFinal1(campo->getAncho(), 125, campo->getVelocidadX(), jugadores);
}

void ExtensionNivel::iniciar() {
	iniciado = true;
	campo->agregarEntidadEnemigo(enemigoFinal);
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
