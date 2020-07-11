#ifndef CUCURUCHO_VIDAJUGADORINVENCIBLE_H
#define CUCURUCHO_VIDAJUGADORINVENCIBLE_H


#include "VidaEntidad.h"

class VidaJugadorInvencible : public VidaEntidad {
public:
	VidaJugadorInvencible(int energia);

	void procesarColision(const int tipoEntidad) override;
};


#endif //CUCURUCHO_VIDAJUGADORINVENCIBLE_H
