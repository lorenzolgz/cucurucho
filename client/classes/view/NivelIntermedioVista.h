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
    SDL_Renderer *gRenderer;

public:
    NivelIntermedioVista(const std::string fondoFilename);
    FondoVista *nuevoFondo(const std::string &archivo);
    void render();
};


#endif //CUCURUCHO_NIVELINTERMEDIOVISTA_H
