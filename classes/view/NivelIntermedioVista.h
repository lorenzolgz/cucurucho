//
// Created by camix on 4/5/20.
//

#ifndef CUCURUCHO_NIVELINTERMEDIOVISTA_H
#define CUCURUCHO_NIVELINTERMEDIOVISTA_H

#include <SDL_render.h>
#include "../../commons/utils/Log.h"
#include "FondoVista.h"

class NivelIntermedioVista {
private:
    FondoVista *fondo;
    SDL_Renderer *gRenderer;
    SDL_Rect posCampo;

public:
    NivelIntermedioVista(int ancho,int alto,int inicioEnEjeY);
    FondoVista *nuevoFondo(const std::string &archivo);
    void render();
};


#endif //CUCURUCHO_NIVELINTERMEDIOVISTA_H
