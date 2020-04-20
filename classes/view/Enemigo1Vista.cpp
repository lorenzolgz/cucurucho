#include "Enemigo1Vista.h"
#include <SDL_image.h>
#include "../Utils.h"
#include "../Log.h"
#include "../GeneradorDeTexturas.h"

Enemigo1Vista::Enemigo1Vista(SDL_Renderer* gRenderer) {
	Enemigo1Vista::gRenderer = gRenderer;
	//Enemigo1Vista::textura = cargarTextura(gRenderer, "enemy01.png");
    GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
	Enemigo1Vista::textura = generadorDeTexturas->generarTextura(gRenderer, "enemy01.png");
	l.info("Enemy 01 created");
}

void Enemigo1Vista::render(Vector posicion, int velocidadX) {
	SDL_Rect srcrect = {0 + ENEMIGO1_SRC_ANCHO * (velocidadX < 10) * (velocidadX > 5)
						+ ENEMIGO1_SRC_ANCHO * 2 * (velocidadX > 10) * (velocidadX < 15)
						+ ENEMIGO1_SRC_ANCHO * 3 * (velocidadX > 15),
						0 , ENEMIGO1_SRC_ANCHO, ENEMIGO1_SRC_ALTO};
	SDL_Rect dstrect = {(int) posicion.getX(), (int) posicion.getY(), ENEMIGO1_SRC_ANCHO, ENEMIGO1_SRC_ALTO};

	SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
}
