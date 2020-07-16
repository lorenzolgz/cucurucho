//
// Created by ailen-magali on 19/4/20.
//

#ifndef CUCURUCHO_GENERADORDETEXTURAS_H
#define CUCURUCHO_GENERADORDETEXTURAS_H


#include <SDL_render.h>
#include <string>
#include <map>
#include <iostream>
#include "GraphicRenderer.h"
#include "../../commons/utils/Log.h"
#include <SDL_render.h>
#include <SDL_image.h>

using namespace std;

class GeneradorDeTexturas {
public:
    static GeneradorDeTexturas *getInstance();
    SDL_Texture* generarTextura(string entidadDelJuego);

private:
    GeneradorDeTexturas();
	static GeneradorDeTexturas *instance;
    map<string, SDL_Texture*> texturas;
    SDL_Texture* textura_defecto;
    SDL_Texture * cargarTextura(SDL_Renderer* gRenderer, const std::string& path);
};

#endif //CUCURUCHO_GENERADORDETEXTURAS_H
