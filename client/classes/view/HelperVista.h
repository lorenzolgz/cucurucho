#ifndef CUCURUCHO_HELPERVISTA_H
#define CUCURUCHO_HELPERVISTA_H

#include <array>
#include <deque>
#include <SDL_render.h>
#include "../../../commons/utils/Vector.h"
#include "Colores.h"
#include "JugadorVista.h"

const int HELPER_BALL_SRC_RADIO = 24;
const int HELPER_SRC_DISTANCIA = 27;

const int HELPER_SRC_ANCHO = 48;
const int HELPER_SRC_ALTO = 48;


class HelperVista {
public:
	HelperVista();
	void render(struct EstadoHelper estadoHelper, ColoresJugador coloresJugador, bool presente);

private:
	SDL_Renderer* gRenderer;
	SDL_Texture* textura;
    SDL_Texture *texturaBall;
    int contador;
    std::deque<Vector> recorrido;

	void renderGlow(Vector posicion, std::deque<Vector> recorrido, ColoresJugador coloresJugador);
	void renderBall(Vector posicion, ColoresJugador coloresJugador);
	void renderHelper(Vector posicion, double angulo, ColoresJugador coloresJugador);
};


#endif //CUCURUCHO_HELPERVISTA_H
