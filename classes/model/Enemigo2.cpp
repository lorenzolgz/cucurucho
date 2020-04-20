#include "Enemigo2.h"
#include <SDL_image.h>
#include "../Utils.h"
#include "../Log.h"

const int OFFSET_A = 600;
const int OFFSET_B = 1500;

Enemigo2::Enemigo2(float x,float y) {
    velocidadEscalar = 1;
    posicion = Vector(x, y);
	velocidadX = true;
    vista = new Enemigo2Vista();
    l.info("Enemy 02 created");
}

void Enemigo2::tick() {
	recalcularPosicion();
	vista->render(posicion, velocidadX);
	l.info(("Position ENEMY 02:("+ std::to_string(posicion.getX())+","+ std::to_string(posicion.getY())+ ")"));
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
