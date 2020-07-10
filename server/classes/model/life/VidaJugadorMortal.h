#ifndef CUCURUCHO_VIDAJUGADORMORTAL_H
#define CUCURUCHO_VIDAJUGADORMORTAL_H


#include "VidaEntidad.h"

class VidaJugadorMortal : public VidaEntidad {
public:
	VidaJugadorMortal(int energia);

protected:
	int danioColisionEnemigo1() override;
};


#endif //CUCURUCHO_VIDAJUGADORMORTAL_H
