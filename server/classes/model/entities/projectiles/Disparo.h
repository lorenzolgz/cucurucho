//
// Created by lorenzo on 7/9/20.
//

#ifndef CUCURUCHO_DISPARO_H
#define CUCURUCHO_DISPARO_H


#include "../../../../../commons/protocols/protocolo.h"
#include "../../../../../commons/utils/Vector.h"
#include "../Entidad.h"

class Disparo : public Entidad {
public:
    Disparo(float x, float y, int nroJugador);

	EstadoDisparo state();
	float getVelocidad();
	Vector getPosicion() override;
    int getAncho() override ;
	int getAlto() override ;
    void tick() override;
	int getTipoEntidad() override;
	std::list<Forma> getFormas() override;
	VidaEntidad *getVidaEntidad() override;

private:
	int nroJugador;
    Vector posicion;
	float velocidad;
	VidaEntidad *vida;
};


#endif //CUCURUCHO_DISPARO_H
