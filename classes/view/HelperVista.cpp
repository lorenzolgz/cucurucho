#include "HelperVista.h"
#include "../Utils.h"
#include "../GraphicRenderer.h"


HelperVista::HelperVista(Jugador *jugador, ColoresJugador colores) {
	HelperVista::gRenderer = GraphicRenderer::getInstance();
	HelperVista::jugador = jugador;
    HelperVista::colores = colores;
	GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
    HelperVista::textura = generadorDeTexturas->generarTextura("helper.png");
    HelperVista::texturaBall = generadorDeTexturas->generarTextura("helper-ball.png");
}

void HelperVista::render(Vector posicion, double angulo, std::deque<Vector> recorrido) {
	renderGlow(posicion, recorrido);
	renderBall(posicion);
	renderHelper(posicion, angulo);
}


void HelperVista::renderGlow(Vector posicion, std::deque<Vector> recorrido) {
	int contador = jugador->getContador();

    std::array<int, 3> color = colores.getColorGlow(contador);
	SDL_SetTextureColorMod(texturaBall, color[0], color[1], color[2]);

	SDL_Rect glowsrc = {0, HELPER_SRC_ANCHO, HELPER_SRC_ANCHO, HELPER_SRC_ANCHO};
	SDL_Rect glowdst = {(int) posicion.getX() - HELPER_BALL_SRC_RADIO,
						(int) posicion.getY() - HELPER_BALL_SRC_RADIO,
						HELPER_SRC_ALTO, HELPER_SRC_ANCHO};

	SDL_RenderCopy(gRenderer, texturaBall, &glowsrc, &glowdst);

	if (contador % 7 < 3) {
		// Una de las tres posibles particulas [0, 1, 2]
		int glow = contador % 7;
		glowsrc = {HELPER_SRC_ANCHO * glow, HELPER_SRC_ALTO, HELPER_SRC_ANCHO, HELPER_SRC_ALTO};
		glowdst = {(int) recorrido[6 * (glow + 1)].getX() - HELPER_BALL_SRC_RADIO,
				   (int) recorrido[6 * (glow + 1)].getY() - HELPER_BALL_SRC_RADIO,
				   HELPER_SRC_ANCHO, HELPER_SRC_ALTO };
		SDL_RenderCopy(gRenderer, texturaBall, &glowsrc, &glowdst);
	}

	SDL_SetTextureColorMod(texturaBall, 255, 255, 255);
}


void HelperVista::renderBall(Vector posicion) {
	SDL_Rect ballsrc = {0, 0, HELPER_SRC_ANCHO, HELPER_SRC_ALTO};
	SDL_Rect balldst = {(int) posicion.getX() - HELPER_BALL_SRC_RADIO,
						(int) posicion.getY() - HELPER_BALL_SRC_RADIO,
						HELPER_SRC_ANCHO, HELPER_SRC_ALTO};

	SDL_RenderCopy(gRenderer, texturaBall, &ballsrc, &balldst);

	ballsrc.x += HELPER_SRC_ANCHO;
	SDL_SetTextureColorMod(texturaBall, colores.base[0][0], colores.base[0][1], colores.base[0][2]);
    SDL_RenderCopy(gRenderer, texturaBall, &ballsrc, &balldst);
    SDL_SetTextureColorMod(texturaBall, 255, 255, 255);
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
	for (int i = 0; i < 2; i++) {
        SDL_SetTextureColorMod(textura, colores.base[0][0], colores.base[0][1], colores.base[0][2]);
        helpersrc.y += HELPER_SRC_ALTO;
        SDL_RenderCopyEx(gRenderer, textura, &helpersrc, &helperdst, -(int) (angulo / 90) * 90, nullptr, SDL_FLIP_NONE);
	}
    SDL_SetTextureColorMod(textura, 255, 255, 255);

}
