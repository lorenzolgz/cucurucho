//
// Created by javier on 10/4/20.
//

#ifndef CPP_SANDBOX_JUGADOR_H
#define CPP_SANDBOX_JUGADOR_H


#include <SDL_render.h>
#include <string>
#include "../Vector.h"
#include "../view/JugadorView.h"

const double JUGADOR_VELOCIDAD_ESCALAR = 4.5;

class Jugador {
public:
	Jugador(SDL_Renderer* gRenderer, int x, int y);
	void render();
	void calcularVectorVelocidad(bool arriba, bool abajo, bool izquierda, bool derecha);

    const Vector &getPosicion() const;

    const Vector getVelocidad() const;

    int getContador() const;

private:
    Vector posicion;
    Vector velocidad;
    double velocidadEscalar;
    int contadorVelocidadY;

	JugadorView *view;
};


#endif //CPP_SANDBOX_JUGADOR_H
