//
// Created by javier on 10/5/20.
//

#ifndef CUCURUCHO_TITULO_H
#define CUCURUCHO_TITULO_H

#include "Ticker.h"
#include "../view/TituloVista.h"
#include <string>

const int INICIO_TIMEOUT = 120;

class Titulo: public Ticker {
public:
    Titulo(int ancho, int alto);
    void tick() override;

    bool isActivada(bool enter);

private:
    TituloVista* tituloVista;
    int contador;
    bool activada;
};

#endif //CUCURUCHO_TITULO_H
