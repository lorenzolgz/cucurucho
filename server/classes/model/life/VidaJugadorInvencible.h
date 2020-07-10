#ifndef CUCURUCHO_VIDAJUGADORINVENCIBLE_H
#define CUCURUCHO_VIDAJUGADORINVENCIBLE_H


#include "VidaEntidad.h"

// Todo: En realidad tiene que perder vida pero no morir cuando queda en 0 !!!!
class VidaJugadorInvencible : public VidaEntidad {
public:
	VidaJugadorInvencible();

	int getEnergiaInicial() override;
	void procesarColision(const int tipoEntidad) override;
};


#endif //CUCURUCHO_VIDAJUGADORINVENCIBLE_H
