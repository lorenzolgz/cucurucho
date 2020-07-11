#ifndef CUCURUCHO_ENEMIGOFINAL1VISTA_H
#define CUCURUCHO_ENEMIGOFINAL1VISTA_H


#include <SDL_render.h>
#include "../../../commons/protocols/protocolo.h"

const int ENEMIGO_FINAL1_SRC_ANCHO = 375;
const int ENEMIGO_FINAL1_SRC_ALTO = 288;

class EnemigoFinal1Vista {
public:
	EnemigoFinal1Vista();
	void render(EstadoEnemigo estadoEnemigo);

private:
	SDL_Renderer* gRenderer;
	SDL_Texture* textura;
};


#endif //CUCURUCHO_ENEMIGOFINAL1VISTA_H
