#include "Enemigo2.h"
#include <SDL_image.h>
#include "../../../commons/utils/Utils.h"
#include "../../../commons/utils/Log.h"
#include "Nivel.h"

const int OFFSET_A = 600;
const int OFFSET_B = 1500;

Enemigo2::Enemigo2(float x,float y, float velocidadX) {
    if (random() % 2 == 0) {
        x = -x + PANTALLA_ANCHO - ENEMIGO2_ANCHO;
        velocidadX *= -1;
    }
	Enemigo2::velocidadEscalar = 1;
	Enemigo2::posicion = Vector(x, y);
	Enemigo2::velocidadX = velocidadX;
    l->info("Se creo correctamente el Enemigo 02.");
}

int Enemigo2::getAncho() {
	return ENEMIGO2_ANCHO;
}

int Enemigo2::getAlto() {
	return ENEMIGO2_ALTO;
}

void Enemigo2::tick() {
	posicion = Vector(posicion.getX() - velocidadX, posicion.getY());
	l->debug("Posicion del Enemigo 02: "+ posicion.getVector());
}

void Enemigo2::recalcularPosicion() {
// Por si queremos mostrar como entra y sale en loop, moficando el sprite dependiendo
// si avanza o retrocede
//
    if (posicion.getX() > OFFSET_A and velocidadX) {
        posicion = posicion + Vector(-velocidadEscalar, 0);
        if (posicion.getX() <= OFFSET_A) velocidadX = false;
    } else{
        posicion = posicion + Vector(velocidadEscalar, 0);
        if (posicion.getX() >= OFFSET_B) velocidadX = true;
    }
}

Vector Enemigo2::getPosicion() {
	return posicion;
}
