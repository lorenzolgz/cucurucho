//
// Created by rodrigosouto on 18/4/20.
//

#include "JugadorView.h"
#include "../Utils.h"
#include "../Log.h"

JugadorView::JugadorView(SDL_Renderer* gRenderer) {
	JugadorView::gRenderer = gRenderer;
	JugadorView::textura = cargarTextura(gRenderer, "player.png");
	JugadorView::texturaGlow = cargarTextura(gRenderer, "player.png");
	JugadorView::contador = 0;
	l.info("Player view created");
}

void JugadorView::render(Vector posicion, int contadorVelocidadY) {
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

	l.info(("Position PLAYER:("+ std::to_string(posicion.getX())+","+ std::to_string(posicion.getY())+ ")"));
}

void JugadorView::colorGlow() {
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

int JugadorView::getContador() const {
	return contador;
}
