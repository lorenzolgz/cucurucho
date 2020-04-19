//
// Created by rodrigosouto on 19/4/20.
//

#ifndef CUCURUCHO_ENEMIGO2VISTA_H
#define CUCURUCHO_ENEMIGO2VISTA_H

#include <SDL_render.h>
#include <string>
#include "../Vector.h"

const int ENEMIGO2_ANCHOS = 285;
const int ENEMIGO2_ALTOS = 147;

class Enemigo2Vista {
public:
	Enemigo2Vista(SDL_Renderer* gRenderer);
	void render(Vector posicion, int velociadadX);

private:
	SDL_Renderer* gRenderer;
	SDL_Texture* textura;

	SDL_Rect generarDstrect(Vector posicion, int ancho, int alto);
};


#endif //CUCURUCHO_ENEMIGO2VISTA_H
