#ifndef CUCURUCHO_JUGADORVISTA_H
#define CUCURUCHO_JUGADORVISTA_H

#include <SDL_render.h>
#include <string>
#include "../Vector.h"
#include "Colores.h"

const int JUGADOR_SRC_ANCHO = 96;
const int JUGADOR_SRC_ALTO = 48;

class JugadorVista {
public:
    JugadorVista(ColoresJugador jugador);
	void render(Vector posicion, int contadorVelocidadY);
	int getContador() const;

private:
	SDL_Renderer* gRenderer;
	SDL_Texture* textura;
    ColoresJugador colores = ColoresJugador({}, {});
	int contador;

	void colorGlow();
    void colorShip(SDL_Rect srcrect, SDL_Rect dstrect);
};


#endif //CUCURUCHO_JUGADORVISTA_H
