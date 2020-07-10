#include "VidaProyectil.h"

#define PROYECTIL_ENERGIA_INICIAL 1

VidaProyectil::VidaProyectil() {
	vivir();
}

int VidaProyectil::getEnergiaInicial() {
	return PROYECTIL_ENERGIA_INICIAL;
}
