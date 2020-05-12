//
// Created by javier on 10/5/20.
//

#include "Titulo.h"
#include "../Log.h"

Titulo::Titulo(int ancho, int alto) {
    activada = false;
    contador = 0;
    Titulo::tituloVista = new TituloVista(ancho, alto);
    l.info("La pantalla incial fue creada correctamente.");
}

void Titulo::tick() {
    tituloVista->render(activada);
    if (activada) contador++;
}

bool Titulo::isActivada(bool enter) {
    if (enter) activada = true;
    return activada && contador > INICIO_TIMEOUT;
}
