#include "Enemigo2Vista.h"
#include <SDL_image.h>
#include "../Utils.h"
#include "../Log.h"
#include "../GeneradorDeTexturas.h"
#include "../GraphicRenderer.h"

Enemigo2Vista::Enemigo2Vista() {
	Enemigo2Vista::gRenderer = GraphicRenderer::getInstance();
	//Enemigo2Vista::textura = cargarTextura(gRenderer, "enemy02.png");
    GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
    Enemigo2Vista::textura = generadorDeTexturas->generarTextura("enemy02.png");
}

void Enemigo2Vista::render(Vector posicion, int velocidadX) {
	SDL_Rect srcrect = {0, 0 + ENEMIGO2_SRC_ALTOS * (velocidadX), ENEMIGO2_SRC_ANCHO, ENEMIGO2_SRC_ALTOS};
	SDL_Rect dstrect = {(int) posicion.getX(), (int) posicion.getY(), ENEMIGO2_SRC_ANCHO, ENEMIGO2_SRC_ALTOS};

	SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
}
