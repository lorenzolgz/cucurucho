#ifndef CUCURUCHO_VIDAENEMIGOFINAL1_H
#define CUCURUCHO_VIDAENEMIGOFINAL1_H


#include "VidaEntidad.h"

class VidaEnemigoFinal1 : public VidaEntidad {
public:
	VidaEnemigoFinal1();

	int danioColisionDisparoJugador() override;
};


#endif //CUCURUCHO_VIDAENEMIGOFINAL1_H
