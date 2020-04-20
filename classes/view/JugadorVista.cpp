#include "JugadorVista.h"
#include "../Utils.h"
#include "../Log.h"
#include "../GeneradorDeTexturas.h"
#include "../GraphicRenderer.h"

JugadorVista::JugadorVista() {
	JugadorVista::gRenderer = GraphicRenderer::getInstance();
	//JugadorVista::textura = cargarTextura(gRenderer, "player.png");
	//JugadorVista::texturaGlow = cargarTextura(gRenderer, "player.png");
    GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
    JugadorVista::textura = generadorDeTexturas->generarTextura("player.png");
    JugadorVista::texturaGlow = generadorDeTexturas->generarTextura("player.png");
	JugadorVista::contador = 0;
	l.info("Player view created");
}

void JugadorVista::render(Vector posicion, int contadorVelocidadY) {
	SDL_Rect srcrect = {JUGADOR_SRC_ANCHO + JUGADOR_SRC_ANCHO * 2 * (contadorVelocidadY < -10) + JUGADOR_SRC_ANCHO * 4 * (contadorVelocidadY > 10),
						0, JUGADOR_SRC_ANCHO, JUGADOR_SRC_ALTO};

	SDL_Rect dstrect = {(int) posicion.getX(),
						(int) posicion.getY(),
						JUGADOR_SRC_ANCHO,
						JUGADOR_SRC_ALTO};

	SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);

	colorGlow();
	srcrect = {JUGADOR_SRC_ANCHO * 2 * (contadorVelocidadY < -10) + JUGADOR_SRC_ANCHO * 4 * (contadorVelocidadY > 10),
			   0, JUGADOR_SRC_ANCHO, JUGADOR_SRC_ALTO};
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
