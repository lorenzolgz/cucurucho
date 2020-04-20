#ifndef CPP_SANDBOX_JUGADOR_H
#define CPP_SANDBOX_JUGADOR_H


#include <SDL_render.h>
#include <string>
#include "../Vector.h"
#include "../view/JugadorVista.h"
#include "../GeneradorDeTexturas.h"

const double JUGADOR_VELOCIDAD_ESCALAR = 4.5;

class Jugador {
public:
	Jugador(SDL_Renderer* gRenderer, int x, int y);
	void calcularVectorVelocidad(bool arriba, bool abajo, bool izquierda, bool derecha);
	void tick();

    const Vector &getPosicion() const;
    const Vector getVelocidad() const;
    int getContador() const;

private:
    Vector posicion;
    Vector velocidad;
    double velocidadEscalar;
    int contadorVelocidadY;
	JugadorVista *vista;
};


#endif //CPP_SANDBOX_JUGADOR_H
