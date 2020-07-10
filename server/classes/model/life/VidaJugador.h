#ifndef CUCURUCHO_VIDAJUGADOR_H
#define CUCURUCHO_VIDAJUGADOR_H


#include "VidaEntidad.h"

class VidaJugador : public VidaEntidad {
public:
	VidaJugador();

	int getEnergia() override;
	void procesarColision(const int tipoEntidad) override;
	void cambiarInvencible(bool invencible);
	int getCantidadVidas();

private:
	VidaEntidad* vidaInterna;
	bool invencible;
	int cantidadVidas;
};


#endif //CUCURUCHO_VIDAJUGADOR_H
