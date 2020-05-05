//
// Created by camix on 4/5/20.
//

#include "NivelIntermedio.h"
#include "../view/FondoVista.h"

NivelIntermedio::NivelIntermedio(int ancho, int alto, int inicioEnEjeY) {
    NivelIntermedio::nivelIntermedioVista = new NivelIntermedioVista(ancho, alto, inicioEnEjeY);
}

FondoVista * NivelIntermedio::nuevoFondo(const std::string &fileName, float xOffset, int yFondo) {
    return nivelIntermedioVista->nuevoFondo(fileName, xOffset, yFondo);
}

void NivelIntermedio::tick() {
    nivelIntermedioVista->render();
}