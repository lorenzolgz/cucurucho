//
// Created by javier on 12/4/20.
//

#ifndef CUCURUCHO_HELPER_H
#define CUCURUCHO_HELPER_H


#include <array>
#include <deque>
#include "../../../commons/protocols/protocolo.h"
#include "../../../commons/utils/Vector.h"
#include "Jugador.h"
#include "entities/projectiles/Disparo.h"

class Jugador;
class HelperVista;

const int HELPER_BALL_RADIO = 24;
const int HELPER_DISTANCIA = 27;

const double HELPER_VEL_ANGULAR = 15;
const double HELPER_ACELERACION = 0.2;

const int HELPER_ANCHO = 48;
const int HELPER_ALTO = 48;

class Disparo;

class Helper {
public:
    Helper(Jugador* jugador, Vector posRelativa);
    void tick();
	struct EstadoHelper state();

    void setAngulo(double angulo);

	Disparo* disparar();

private:
    Vector posicion;
    Vector velocidad;
    Vector posRelativa;
    Jugador* jugador;
    std::deque<Vector> recorrido;
    double velAngular;
    double angulo;
    double aceleracion;

    void calcularAngulo();
    void calcularVelocidad();
};


#endif //CUCURUCHO_HELPER_H
