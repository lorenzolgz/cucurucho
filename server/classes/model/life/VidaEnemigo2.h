#ifndef CUCURUCHO_VIDAENEMIGO2_H
#define CUCURUCHO_VIDAENEMIGO2_H


#include "VidaEntidad.h"

class VidaEnemigo2 : public VidaEntidad {
public:
	VidaEnemigo2();

	int getEnergiaInicial() override;
	int danioColisionJugador() override;
};


#endif //CUCURUCHO_VIDAENEMIGO2_H