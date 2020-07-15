//
// Created by lorenzo on 7/9/20.
//

#ifndef CUCURUCHO_DISPARO_H
#define CUCURUCHO_DISPARO_H


#include "../../../../../commons/protocols/protocolo.h"
#include "../../../../../commons/utils/Vector.h"
#include "../Entidad.h"
#include "../../Jugador.h"
#include "EntidadDisparo.h"

class Jugador;

class Disparo : public EntidadDisparo {
public:
    Disparo(float x, float y, Jugador* jugador);

	EstadoDisparo state();
	float getVelocidad();
    void tick() override;
	int getTipoEntidad() override;
	void matoEntidad(int tipoEntidad);

private:
	float velocidad;
	Jugador* jugador;
    Vector inicio;
};


#endif //CUCURUCHO_DISPARO_H
