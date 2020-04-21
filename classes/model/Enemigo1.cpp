#include "Enemigo1.h"
#include <SDL_image.h>
#include "../Utils.h"
#include "../Log.h"


Enemigo1::Enemigo1(float x, float y) {
    posicion = Vector(x, y);
	velocidadX = 7; // Posición 2 de sprite
    vista = new Enemigo1Vista();
    l.info("Se creo correctamente el Enemigo 01.");
}

int Enemigo1::getAncho() {
	return ENEMIGO1_ANCHO;
}

int Enemigo1::getAlto() {
	return ENEMIGO1_ALTO;
}

void Enemigo1::tick() {
	vista->render(posicion, velocidadX);
    l.info("Posicion del Enemigo 01: "+ posicion.getVector());
}
