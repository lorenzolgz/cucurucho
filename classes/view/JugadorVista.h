#ifndef CUCURUCHO_JUGADORVISTA_H
#define CUCURUCHO_JUGADORVISTA_H

#include <SDL_render.h>
#include <string>
#include "../Vector.h"

const int JUGADOR_SRC_ANCHO = 96;
const int JUGADOR_SRC_ALTO = 48;

class JugadorVista {
public:
	JugadorVista();
	void render(Vector posicion, int contadorVelocidadY);
	int getContador() const;

private:
	SDL_Renderer* gRenderer;
	SDL_Texture* textura;
	SDL_Texture* texturaGlow;
	int contador;

	void colorGlow();
};


#endif //CUCURUCHO_JUGADORVISTA_H
