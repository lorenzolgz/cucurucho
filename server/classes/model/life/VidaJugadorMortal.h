#ifndef CUCURUCHO_VIDAJUGADORMORTAL_H
#define CUCURUCHO_VIDAJUGADORMORTAL_H


#include "VidaEntidad.h"

class VidaJugadorMortal : public VidaEntidad {
public:
	VidaJugadorMortal();

	int getEnergiaInicial() override;
	int danioColisionEnemigo1() override;
	int danioColisionEnemigo2() override;
};


#endif //CUCURUCHO_VIDAJUGADORMORTAL_H
