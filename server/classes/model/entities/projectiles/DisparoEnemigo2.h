//
// Created by camix on 12/7/20.
//

#ifndef CUCURUCHO_DISPAROENEMIGO2_H
#define CUCURUCHO_DISPAROENEMIGO2_H


#include "EntidadDisparo.h"
#include "../../life/VidaProyectil.h"
#include "../../../../../commons/utils/Vector.h"

#define ANCHO_DISPARO_ENEMIGO2 18
#define ALTO_DISPARO_ENEMIGO2 18
#define VELOCIDAD_DISPARO_ENEMIGO2 5
#define ID_ENEMIGO2 -2

class DisparoEnemigo2: public EntidadDisparo {
public:
    DisparoEnemigo2(Vector posicion, Vector direccion);

    EstadoDisparo state();
    float getVelocidad();
    void tick() override;
    int getTipoEntidad() override;

private:
    int nroJugador;
	Vector velocidad;
};



#endif //CUCURUCHO_DISPAROENEMIGO2_H
