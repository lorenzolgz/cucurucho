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
#define VELOCIDAD_DISPARO_ENEMIGO2 7
#define ID_ENEMIGO2 -2

class DisparoEnemigo2: public EntidadDisparo {
public:
    DisparoEnemigo2(float x, float y);

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



#endif //CUCURUCHO_DISPAROENEMIGO2_H
