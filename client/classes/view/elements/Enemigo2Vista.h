#ifndef CUCURUCHO_ENEMIGO2VISTA_H
#define CUCURUCHO_ENEMIGO2VISTA_H

#include <SDL_render.h>
#include <string>
#include "../../../../commons/utils/Vector.h"
#include "../../../../commons/protocols/protocolo.h"
#include "ExplosionVista.h"

const int ENEMIGO2_SRC_ANCHO = 285;
const int ENEMIGO2_SRC_ALTO = 147;

class Enemigo2Vista {
public:
	Enemigo2Vista();
	void render(EstadoEnemigo estadoEnemigo);
    ExplosionVista *nuevaExplosion(Vector vector);

private:
	SDL_Renderer* gRenderer;
	SDL_Texture* textura;
};


#endif //CUCURUCHO_ENEMIGO2VISTA_H
