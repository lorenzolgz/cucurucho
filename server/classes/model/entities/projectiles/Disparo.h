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

#define ANCHO_DISPARO_JUGADOR 96
#define ALTO_DISPARO_JUGADOR 24
#define VELOCIDAD_DISPARO_JUGADOR 13

class Jugador;

class Disparo : public EntidadDisparo {
public:
    Disparo(float x, float y, Jugador* jugador);

	Disparo(Vector posicion, Vector velocidad, int ancho, int alto, Jugador *jugador);

	EstadoDisparo state();
	Vector getVelocidad();
    void tick() override;
	int getTipoEntidad() override;
	void matoEntidad(int tipoEntidad);

private:
	Vector velocidad;
	Jugador* jugador;
    Vector inicio;
    int helper;
};


#endif //CUCURUCHO_DISPARO_H
