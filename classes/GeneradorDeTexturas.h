//
// Created by ailen-magali on 19/4/20.
//

#ifndef CUCURUCHO_GENERADORDETEXTURAS_H
#define CUCURUCHO_GENERADORDETEXTURAS_H


#include <SDL_render.h>
#include <string>
#include <map>
#include <iostream>
#include "Utils.h"
using namespace std;

class GeneradorDeTexturas {
public:
    static GeneradorDeTexturas *getInstance();
    SDL_Texture* generarTextura(SDL_Renderer* gRenderer, string entidadDelJuego);

private:
    static GeneradorDeTexturas *instance;
    GeneradorDeTexturas();
};

#endif //CUCURUCHO_GENERADORDETEXTURAS_H
