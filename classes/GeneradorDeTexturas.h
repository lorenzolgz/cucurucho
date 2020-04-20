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
    SDL_Texture* generarTextura(string entidadDelJuego);

private:
    GeneradorDeTexturas();
	static GeneradorDeTexturas *instance;
};

#endif //CUCURUCHO_GENERADORDETEXTURAS_H
