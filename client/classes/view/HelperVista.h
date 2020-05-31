#ifndef CUCURUCHO_HELPERVISTA_H
#define CUCURUCHO_HELPERVISTA_H

#include <array>
#include <deque>
#include <SDL_render.h>
#include "../Vector.h"
#include "Colores.h"
#include "JugadorVista.h"

const int HELPER_BALL_SRC_RADIO = 24;
const int HELPER_SRC_DISTANCIA = 27;

const int HELPER_SRC_ANCHO = 48;
const int HELPER_SRC_ALTO = 48;


class HelperVista {
public:
	HelperVista(ColoresJugador coloresJugador);
	void render(Vector posicion, double angulo);

private:
	SDL_Renderer* gRenderer;
	SDL_Texture* textura;
    SDL_Texture *texturaBall;
    int contador;
    std::deque<Vector> recorrido;

	void renderGlow(Vector posicion, std::deque<Vector> recorrido);
	void renderBall(Vector posicion);
	void renderHelper(Vector posicion, double angulo);

    ColoresJugador colores = ColoresJugador({}, {});
};


#endif //CUCURUCHO_HELPERVISTA_H
