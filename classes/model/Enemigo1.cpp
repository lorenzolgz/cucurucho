#include "Enemigo1.h"
#include <SDL_image.h>
#include "../Utils.h"
#include "../Log.h"


Enemigo1::Enemigo1(SDL_Renderer* gRenderer, float x, float y) {
    posicion = Vector(x, y);
	velocidadX = 7; // Posición 2 de sprite
    vista = new Enemigo1Vista(gRenderer);
    l.info("Enemy 01 created");
};

void Enemigo1::tick() {
	vista->render(posicion, velocidadX);
	l.info(("Position ENEMY 01:("+ std::to_string(posicion.getX())+","+ std::to_string(posicion.getX())+ ")"));
}
