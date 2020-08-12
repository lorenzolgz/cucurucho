//
// Created by javier on 19/7/20.
//

#ifndef CUCURUCHO_VIDAENEMIGOFINAL1EXT_H
#define CUCURUCHO_VIDAENEMIGOFINAL1EXT_H


#include "VidaEntidad.h"

class VidaEnemigoFinal1Ext : public VidaEntidad {
public:
	VidaEnemigoFinal1Ext();

	int danioColisionJugador() override;
	int danioColisionDisparoJugador() override;
};


#endif //CUCURUCHO_VIDAENEMIGOFINAL1EXT_H
