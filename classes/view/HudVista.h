#ifndef CUCURUCHO_HUDVISTA_H
#define CUCURUCHO_HUDVISTA_H


#include <SDL_render.h>
#include "../Vector.h"

const int HUD_SRC_ANCHO = 960;
const int HUD_SRC_ALTO = 96;

class HudVista {
public:
	HudVista(SDL_Renderer* gRenderer);
	void render(Vector posicion);
private:
	SDL_Renderer* gRenderer;
	SDL_Texture* textura;
};


#endif //CUCURUCHO_HUDVISTA_H
