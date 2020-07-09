#ifndef CUCURUCHO_VIDAJUGADOR_H
#define CUCURUCHO_VIDAJUGADOR_H


#include "VidaEntidad.h"

class VidaJugador : public VidaEntidad {
public:
	VidaJugador();

	int getEnergiaInicial() override;

	// Overriden methods for template method.
	int danioColisionEnemigo1() override;
	int danioColisionEnemigo2() override;
};


#endif //CUCURUCHO_VIDAJUGADOR_H
