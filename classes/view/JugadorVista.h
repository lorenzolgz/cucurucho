#ifndef CUCURUCHO_JUGADORVISTA_H
#define CUCURUCHO_JUGADORVISTA_H

#include <SDL_render.h>
#include <string>
#include "../Vector.h"


const int JUGADOR_ALTO = 48;
const int JUGADOR_ANCHO = 96;

class JugadorVista {
public:
	JugadorVista(SDL_Renderer* gRenderer);
	void render(Vector posicion, int contadorVelocidadY);
	void calcularVectorVelocidad(bool arriba, bool abajo, bool izquierda, bool derecha);

	const Vector &getPosicion() const;

	const Vector getVelocidad() const;

	int getContador() const;

private:
	SDL_Renderer* gRenderer;
	SDL_Texture* textura;
	SDL_Texture* texturaGlow;
	int contador;

	void colorGlow();
};


#endif //CUCURUCHO_JUGADORVISTA_H
