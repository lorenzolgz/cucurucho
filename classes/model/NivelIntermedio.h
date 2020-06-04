//
// Created by camix on 4/5/20.
//

#ifndef CUCURUCHO_NIVELINTERMEDIO_H
#define CUCURUCHO_NIVELINTERMEDIO_H

#include "Ticker.h"
#include "../view/NivelIntermedioVista.h"
#include <string>


class NivelIntermedio: public Ticker {
public:
    NivelIntermedio(int ancho, int alto, int inicioEnEjeY,char* archivo);
    void tick() override;

private:
    NivelIntermedioVista* nivelIntermedioVista;
    FondoVista *fondo;
};


#endif //CUCURUCHO_NIVELINTERMEDIO_H
