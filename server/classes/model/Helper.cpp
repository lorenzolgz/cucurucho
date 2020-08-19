//
// Created by javier on 12/4/20.
//

#include "Helper.h"
#include "../../../commons/utils/Constantes.h"


Helper::Helper(Jugador* jugador, Vector posRelativa) {
    Helper::jugador = jugador;
    Helper::posRelativa = posRelativa - Vector(HELPER_BALL_RADIO, HELPER_BALL_RADIO)+ Vector(1000000, 1000) * !HELPERS_ACTIVADOS;
    Helper::posicion = posRelativa + jugador->getPosicion();
    Helper::velocidad = Vector(0, 0);
    Helper::velAngular = HELPER_VEL_ANGULAR;
    Helper::aceleracion = HELPER_ACELERACION;
    Helper::angulo = 0;
	for (int i = 0; i < 19; i++) {
        recorrido.push_front(posicion);
    }
}

void Helper::tick() {
	calcularAngulo();
	calcularVelocidad();
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

struct EstadoHelper Helper::state() {
	struct EstadoHelper view;
	view.posicionX = posicion.getX();
	view.posicionY = posicion.getY();
	view.angulo = angulo;
	return view;
}

void Helper::setAngulo(double angulo) {
    Helper::angulo = angulo;
}

Disparo* Helper::disparar() {
	Vector velocidad_d = Vector().polares(VELOCIDAD_DISPARO_JUGADOR, angulo);
	Vector posicion_d = posicion
			+ Vector(HELPER_BALL_RADIO / 5, HELPER_BALL_RADIO / 5)
			- velocidad_d.escalar(HELPER_BALL_RADIO);
	Disparo* disparo = new Disparo(posicion_d, velocidad_d, HELPER_BALL_RADIO * 14 / 8, HELPER_BALL_RADIO * 14 / 8, this->jugador);
	return disparo;
}