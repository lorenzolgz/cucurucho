//
// Created by lorenzo on 7/9/20.
//

#ifndef CUCURUCHO_DISPARO_H
#define CUCURUCHO_DISPARO_H


#include "../../../commons/protocols/protocolo.h"

class Disparo {
public:
    Disparo(float x, float y, int id, int ancho, int alto, float velocidad);
    float getX();
    float getY();
    float getVelocidad();
    int getAncho();
    int getAlto();
    int getId();
    void tick();
    EstadoDisparo state();

private:
    float x;
    float y;
    float velocidad;
    int id;
    int ancho;
    int alto;
};


#endif //CUCURUCHO_DISPARO_H
