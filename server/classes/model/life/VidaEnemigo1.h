#ifndef CUCURUCHO_VIDAENEMIGO1_H
#define CUCURUCHO_VIDAENEMIGO1_H


#include "VidaEntidad.h"

class VidaEnemigo1 : public VidaEntidad {
public:
	VidaEnemigo1();

	int danioColisionDisparoJugador() override;
};


#endif //CUCURUCHO_VIDAENEMIGO1_H
