//
// Created by rodrigosouto on 19/4/20.
//

#include "Enemigo2Vista.h"
#include <SDL_image.h>
#include "../Utils.h"
#include "../Log.h"

const int OFFSET_A = 600;
const int OFFSET_B = 1500;

Enemigo2Vista::Enemigo2Vista(SDL_Renderer* gRenderer) {
	Enemigo2Vista::gRenderer = gRenderer;
	Enemigo2Vista::textura = cargarTextura(gRenderer, "enemy02.png");
	l.info("Enemy 02 created");
};

void Enemigo2Vista::render(Vector posicion, int VelocidadX) {
	SDL_Rect srcrect = {0, 0 + ENEMIGO2_ALTOS * (VelocidadX), ENEMIGO2_ANCHOS, ENEMIGO2_ALTOS};
	// SDL_Rect dstrect = calcularMovimiento(ENEMIGO2_ANCHO, ENEMIGO2_ALTO);

	SDL_Rect dstrect;
	dstrect.x = (int) posicion.getX();
	dstrect.y = (int) posicion.getY();
	dstrect.w = ENEMIGO2_ANCHOS;
	dstrect.h = ENEMIGO2_ALTOS;

	SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
	l.info(("Position ENEMY 02:("+ std::to_string(posicion.getX())+","+ std::to_string(posicion.getY())+ ")"));
}
