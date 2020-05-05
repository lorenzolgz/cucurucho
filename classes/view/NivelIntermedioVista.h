//
// Created by camix on 4/5/20.
//

#ifndef CUCURUCHO_NIVELINTERMEDIOVISTA_H
#define CUCURUCHO_NIVELINTERMEDIOVISTA_H

#include <SDL_render.h>
#include "../Log.h"
#include "FondoVista.h"

class NivelIntermedioVista {
private:
    FondoVista *fondo;

public:
    NivelIntermedioVista(int ancho,int alto,int inicioEnEjeY);

    SDL_Renderer *gRenderer;
    SDL_Rect posCampo;

    FondoVista *nuevoFondo(const std::string &archivo, float xOffset, int yFondo);

    void render();
};


#endif //CUCURUCHO_NIVELINTERMEDIOVISTA_H
