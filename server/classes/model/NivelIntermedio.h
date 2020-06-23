//
// Created by camix on 4/5/20.
//

#ifndef CUCURUCHO_NIVELINTERMEDIO_H
#define CUCURUCHO_NIVELINTERMEDIO_H

#include "Ticker.h"
#include <string>


class NivelIntermedio: public Ticker {
public:
    NivelIntermedio(int ancho, int alto, int inicioEnEjeY,const std::string &archivo);
    void tick() override;

private:
};


#endif //CUCURUCHO_NIVELINTERMEDIO_H
