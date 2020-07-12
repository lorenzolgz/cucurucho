#ifndef CUCURUCHO_JUGADORVISTA_H
#define CUCURUCHO_JUGADORVISTA_H

#include <SDL_render.h>
#include <string>
#include "../../../commons/utils/Vector.h"
#include "Colores.h"
#include "HelperVista.h"
#include "../../../commons/protocols/protocolo.h"
#include "../Audio.h"


const int JUGADOR_SRC_ANCHO = 96;
const int JUGADOR_SRC_ALTO = 48;

const int BARRA_VIDA_SRC_ANCHO = 69;
const int BARRA_VIDA_SRC_ALTO = 6;

class HelperVista;

class JugadorVista {
public:
    JugadorVista(ColoresJugador jugador);
    void render(struct EstadoJugador estadoJugador);

private:
	SDL_Renderer* gRenderer;
	SDL_Texture* textura;
    SDL_Texture *texturaEnergia;
	HelperVista* helperAbove;
	HelperVista* helperBelow;
	ColoresJugador colores = ColoresJugador({}, {});
	ColoresJugador coloresRender = COLORES_GRIS;
	int contador;
	Vector posicion;

	void renderGlow(SDL_Rect srcrect, SDL_Rect dstrect);
    void renderShip(SDL_Rect srcrect, SDL_Rect dstrect);
    void renderLifebar(int energia);

	void calcularVelocidadY(Vector nuevaPosicion);

    int contadorVelocidadY;

    EfectoSonido *audioPerder;
    EfectoSonido *audioRevivir;

    bool deberiaRenderizar(EstadoJugador estadoJugador);

    void setColores(EstadoJugador jugador);
};


#endif //CUCURUCHO_JUGADORVISTA_H
