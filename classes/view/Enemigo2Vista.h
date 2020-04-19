#ifndef CUCURUCHO_ENEMIGO2VISTA_H
#define CUCURUCHO_ENEMIGO2VISTA_H

#include <SDL_render.h>
#include <string>
#include "../Vector.h"

const int ENEMIGO2_SRC_ANCHO = 285;
const int ENEMIGO2_SRC_ALTOS = 147;

class Enemigo2Vista {
public:
	Enemigo2Vista(SDL_Renderer* gRenderer);
	void render(Vector posicion, int velocidadX);

private:
	SDL_Renderer* gRenderer;
	SDL_Texture* textura;
};


#endif //CUCURUCHO_ENEMIGO2VISTA_H
