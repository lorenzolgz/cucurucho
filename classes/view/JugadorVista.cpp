#include "JugadorVista.h"
#include "../Utils.h"
#include "../Log.h"

JugadorVista::JugadorVista(SDL_Renderer* gRenderer) {
	JugadorVista::gRenderer = gRenderer;
	JugadorVista::textura = cargarTextura(gRenderer, "player.png");
	JugadorVista::texturaGlow = cargarTextura(gRenderer, "player.png");
	JugadorVista::contador = 0;
	l.info("Player view created");
}

void JugadorVista::render(Vector posicion, int contadorVelocidadY) {
	SDL_Rect srcrect = {JUGADOR_ANCHO + JUGADOR_ANCHO * 2 * (contadorVelocidadY < -10) + JUGADOR_ANCHO * 4 * (contadorVelocidadY > 10),
						0, JUGADOR_ANCHO, JUGADOR_ALTO};

	SDL_Rect dstrect = {(int) posicion.getX(),
						(int) posicion.getY(),
						JUGADOR_ANCHO,
						JUGADOR_ALTO};

	SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);

	colorGlow();
	srcrect = {JUGADOR_ANCHO * 2 * (contadorVelocidadY < -10) + JUGADOR_ANCHO * 4 * (contadorVelocidadY > 10),
			   0, JUGADOR_ANCHO, JUGADOR_ALTO};
	SDL_RenderCopy(gRenderer, texturaGlow, &srcrect, &dstrect);
}

void JugadorVista::colorGlow() {
	contador++;

	Uint8 COLORES[16][3] = {{206, 160, 239},
							{173, 138, 239},
							{140, 101, 239},
							{99, 69, 239},
							{66, 32, 239},
							{33, 0, 206},
							{33, 0, 173},
							{0, 0, 140},
							{0, 0, 99},
							{0, 0, 140},
							{33, 0, 173},
							{33, 0, 206},
							{66, 32, 239},
							{99, 69, 239},
							{140, 101, 239},
							{173, 138, 239}};

	SDL_SetTextureColorMod(texturaGlow, COLORES[contador % 16][0], COLORES[contador % 16][1], COLORES[contador % 16][2]);
}

int JugadorVista::getContador() const {
	return contador;
}
