//
// Created by camix on 4/5/20.
//

#include "NivelIntermedio.h"
#include "../view/FondoVista.h"

NivelIntermedio::NivelIntermedio(int ancho, int alto, int inicioEnEjeY,const std::string &archivo) {
    NivelIntermedio::nivelIntermedioVista = new NivelIntermedioVista(ancho, alto, inicioEnEjeY);
    nivelIntermedioVista->nuevoFondo(archivo);
    l.info("El Nivel Intermedio fue creado correctamente.");

}

void NivelIntermedio::tick() {
    nivelIntermedioVista->render();
}