#ifndef CUCURUCHO_HELPERVISTA_H
#define CUCURUCHO_HELPERVISTA_H

#include "../model/Jugador.h"
#include <array>
#include <deque>
#include "../../commons/utils/Vector.h"

class Jugador;

const int HELPER_BALL_SRC_RADIO = 24;
const int HELPER_SRC_DISTANCIA = 27;

const int HELPER_SRC_ANCHO = 48;
const int HELPER_SRC_ALTO = 48;


class HelperVista {
public:
	HelperVista(Jugador *jugador, ColoresJugador coloresJugador);
	void render(Vector posicion, double angulo, std::deque<Vector> recorrido);

private:
	SDL_Renderer* gRenderer;
	SDL_Texture* textura;
    SDL_Texture *texturaBall;

	Jugador* jugador;

	void renderGlow(Vector posicion, std::deque<Vector> recorrido);
	void renderBall(Vector posicion);
	void renderHelper(Vector posicion, double angulo);

    ColoresJugador colores = ColoresJugador({}, {});
};


#endif //CUCURUCHO_HELPERVISTA_H
