#ifndef CUCURUCHO_ENEMIGO1VISTA_H
#define CUCURUCHO_ENEMIGO1VISTA_H

#include <SDL_render.h>
#include <string>
#include "../../commons/utils/Vector.h"

const int ENEMIGO1_SRC_ANCHO = 66;
const int ENEMIGO1_SRC_ALTO = 66;

class Enemigo1Vista {
public:
	Enemigo1Vista();
	void render(Vector posicion, int velocidadX);

private:
	SDL_Renderer* gRenderer;
	SDL_Texture* textura;
};


#endif //CUCURUCHO_ENEMIGO1VISTA_H
