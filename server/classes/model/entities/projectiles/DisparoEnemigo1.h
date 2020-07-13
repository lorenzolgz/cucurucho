//
// Created by camix on 11/7/20.
//

#ifndef CUCURUCHO_DISPAROENEMIGO1_H
#define CUCURUCHO_DISPAROENEMIGO1_H



#include "../../life/VidaProyectil.h"
#include "../../../../../commons/protocols/protocolo.h"
#include "../../../../../commons/utils/Vector.h"
#include "EntidadDisparo.h"

#define ANCHO_DISPARO_ENEMIGO1 18
#define ALTO_DISPARO_ENEMIGO1 18
#define VELOCIDAD_DISPARO_ENEMIGO1 6

#define ID_ENEMIGO1 -1

class DisparoEnemigo1: public EntidadDisparo {
public:
    DisparoEnemigo1(float x, float y);

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

#endif //CUCURUCHO_DISPAROENEMIGO1_H
