#include "Enemigo1.h"
#include "../../../commons/utils/Utils.h"
#include "../../../commons/utils/Log.h"
#include "Nivel.h"
#include "../../../commons/utils/Constantes.h"


Enemigo1::Enemigo1(float x, float y, float velocidadX) {
    if (random() % 2 == 0) {
        x = -x + PANTALLA_ANCHO - ENEMIGO1_ANCHO;
        velocidadX *= -1;
    }
	Enemigo1::posicion = Vector(x, y);
	Enemigo1::velocidadX = velocidadX; // Posición 2 de sprite
    l->info("Se creo correctamente el Enemigo 01.");
}

int Enemigo1::getAncho() {
	return ENEMIGO1_ANCHO;
}

int Enemigo1::getAlto() {
	return ENEMIGO1_ALTO;
}

void Enemigo1::tick() {
	posicion = Vector(posicion.getX() - velocidadX, posicion.getY());
    l->debug("Posicion del Enemigo 01: "+ posicion.getVector());
}

Vector Enemigo1::getPosicion() {
	return posicion;
}

struct EstadoEnemigo Enemigo1::state() {
	struct EstadoEnemigo estado;
	estado.posicionX = posicion.getX();
	estado.posicionY = posicion.getY();
	estado.clase = 1;
	return estado;
}

int Enemigo1::getTipoEntidad() {
	return ENTIDAD_ENEMIGO1;
}
