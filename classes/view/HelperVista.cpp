#include "HelperVista.h"
#include "../Utils.h"
#include "../GraphicRenderer.h"


HelperVista::HelperVista(Jugador* jugador) {
	HelperVista::gRenderer = GraphicRenderer::getInstance();
	HelperVista::jugador = jugador;
	GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
    HelperVista::textura = generadorDeTexturas->generarTextura("helper.png");

	for (int i = 0; i < 19; i++) {
		// recorrido.push_front(posicion);
	}
}

void HelperVista::render(Vector posicion, double angulo, std::deque<Vector> recorrido) {
	renderGlow(posicion, recorrido);
	renderBall(posicion);
	renderHelper(posicion, angulo);
}


void HelperVista::renderGlow(Vector posicion, std::deque<Vector> recorrido) {
	int contador = jugador->getContador();
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

	SDL_SetTextureColorMod(textura, COLORES[contador % 16][0], COLORES[contador % 16][1], COLORES[contador % 16][2]);

	SDL_Rect glowsrc = {0, HELPER_SRC_ANCHO, HELPER_SRC_ALTO, HELPER_SRC_ANCHO};
	SDL_Rect glowdst = {(int) posicion.getX() - HELPER_BALL_SRC_RADIO,
						(int) posicion.getY() - HELPER_BALL_SRC_RADIO,
						HELPER_SRC_ALTO, HELPER_SRC_ANCHO};

	SDL_RenderCopy(gRenderer, textura, &glowsrc, &glowdst);


	if (contador % 6 < 3) {
		// Una de las tres posibles particulas [0, 1, 2]
		int glow = contador % 6;
		glowsrc = {HELPER_SRC_ANCHO * glow, HELPER_SRC_ALTO * 2, HELPER_SRC_ANCHO, HELPER_SRC_ALTO};
		glowdst = {(int) recorrido[6 * (glow + 1)].getX() - HELPER_BALL_SRC_RADIO,
				   (int) recorrido[6 * (glow + 1)].getY() - HELPER_BALL_SRC_RADIO,
				   HELPER_SRC_ANCHO, HELPER_SRC_ALTO };
		SDL_RenderCopy(gRenderer, textura, &glowsrc, &glowdst);
	}

	SDL_SetTextureColorMod(textura, 255, 255, 255);
}


void HelperVista::renderBall(Vector posicion) {
	SDL_Rect ballsrc = {HELPER_SRC_ANCHO, HELPER_SRC_ALTO, HELPER_SRC_ANCHO, HELPER_SRC_ALTO};
	SDL_Rect balldst = {(int) posicion.getX() - HELPER_BALL_SRC_RADIO,
						(int) posicion.getY() - HELPER_BALL_SRC_RADIO,
						HELPER_SRC_ANCHO, HELPER_SRC_ALTO};

	SDL_RenderCopy(gRenderer, textura, &ballsrc, &balldst);
}



void HelperVista::renderHelper(Vector posicion, double angulo) {
	int renderPosX = (int) posicion.getX() - HELPER_BALL_SRC_RADIO + (int) (cos_d(angulo) * HELPER_SRC_DISTANCIA);
	int renderPosY = (int) posicion.getY() - HELPER_BALL_SRC_RADIO - (int) (sin_d(angulo) * HELPER_SRC_DISTANCIA);

	int angulo_trunc = ((int) angulo % 90) - 11;

	SDL_Rect helpersrc = {HELPER_SRC_ANCHO * (angulo_trunc >= 11)
						  + HELPER_SRC_ANCHO * (angulo_trunc >= 33)
						  + HELPER_SRC_ANCHO * (angulo_trunc >= 56)
						  - HELPER_SRC_ANCHO * 3 * (angulo_trunc >= 78),
						  0, HELPER_SRC_ANCHO, HELPER_SRC_ALTO};
	SDL_Rect helperdst = {renderPosX,
						  renderPosY,
						  HELPER_SRC_ANCHO, HELPER_SRC_ALTO};

	SDL_RenderCopyEx(gRenderer, textura, &helpersrc, &helperdst, -(int) (angulo / 90) * 90, nullptr, SDL_FLIP_NONE);
}
