//
// Created by javier on 12/4/20.
//

#include <iostream>
#include "Helper.h"
#include "../../commons/utils/Utils.h"

Helper::Helper(Jugador* jugador, Vector posRelativa, ColoresJugador colores) {
    Helper::jugador = jugador;
    Helper::posRelativa = posRelativa;
    Helper::posicion = posRelativa + jugador->getPosicion();
    Helper::velocidad = Vector(0, 0);
    Helper::velAngular = HELPER_VEL_ANGULAR;
    Helper::aceleracion = HELPER_ACELERACION;
    Helper::angulo = 0;
	Helper::vista = new HelperVista(jugador, colores);
	for (int i = 0; i < 19; i++) {
        recorrido.push_front(posicion);
    }
}

void Helper::tick() {
	calcularAngulo();
	calcularVelocidad();

	vista->render(posicion, angulo, recorrido);
}


void Helper::calcularVelocidad(){
    recorrido.pop_back();
    velocidad = (jugador->getPosicion() + posRelativa - posicion) * aceleracion;
    posicion = posicion + velocidad;
    recorrido.push_front(posicion);
}


void Helper::calcularAngulo(){
    if (jugador->getVelocidad().esNulo()) return;

    int angulo_d = (int) (jugador->getVelocidad().arg() - angulo + 180 + 360) % 360 - 180;

    if (abs(angulo_d) < velAngular) {
        angulo += angulo_d;
    } else {
        angulo += velAngular * ((angulo_d > 0) - (angulo_d < 0));
    }
    angulo = ((int) angulo + 360) % 360;
}
