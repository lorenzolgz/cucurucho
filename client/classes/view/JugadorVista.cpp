#include "JugadorVista.h"
#include "../../../commons/utils/Utils.h"
#include "../../../commons/utils/Log.h"
#include "../GeneradorDeTexturas.h"
#include "../GraphicRenderer.h"
#include "HelperVista.h"
#include "../Audio.h"

JugadorVista::JugadorVista(ColoresJugador colores) {
	JugadorVista::gRenderer = GraphicRenderer::getInstance();
    GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
    JugadorVista::textura = generadorDeTexturas->generarTextura("player.png");
	JugadorVista::contador = 0;
	JugadorVista::contadorVelocidadY = 0;
    JugadorVista::colores = colores;

//  USO EFECTOS DE SONIDO: Creo instancia de efecto que quiero y cuando la necesito audio->play(volumen)
    Audio *audio1 = Audio::getInstante();
    JugadorVista::audioPerder = audio1->generarSoundEffect("sfx-05.wav");
    Audio *audio2 = Audio::getInstante();
    JugadorVista::audioRevivir = audio2->generarSoundEffect("sfx-07.wav");

    helperAbove = new HelperVista();
    helperBelow = new HelperVista();
	l->info("La vista del jugador fue creada correctamente.");
}


void JugadorVista::calcularVelocidadY(Vector nuevaPosicion) {
    if ((posicion - nuevaPosicion).getY() > 0.25) {
        contadorVelocidadY += contadorVelocidadY < 14;
    } else if ((posicion - nuevaPosicion).getY() < -0.25) {
        contadorVelocidadY -= contadorVelocidadY > -14;
    } else {
        contadorVelocidadY += (contadorVelocidadY < 0) - (contadorVelocidadY > 0);
    }

}


//void JugadorVista::render(Vector nuevaPosicion, Vector posHelper1, float argHelper1, Vector posHelper2, float argHelper2) {
void JugadorVista::render(struct EstadoJugador estadoJugador) {
    if (estadoJugador.presente) {
        coloresRender = colores;
        JugadorVista::textura = GeneradorDeTexturas::getInstance()->generarTextura("player.png");
    } else {
        coloresRender = COLORES_GRIS;
        JugadorVista::textura = GeneradorDeTexturas::getInstance()->generarTextura("player-g.png");
    }

    Vector nuevaPosicion = Vector(estadoJugador.posicionX, estadoJugador.posicionY);

    calcularVelocidadY(nuevaPosicion);
    posicion = nuevaPosicion;

	SDL_Rect srcrect = {JUGADOR_SRC_ANCHO + JUGADOR_SRC_ANCHO * 2 * (contadorVelocidadY < -10) + JUGADOR_SRC_ANCHO * 4 * (contadorVelocidadY > 10),
						0, JUGADOR_SRC_ANCHO, JUGADOR_SRC_ALTO};

	SDL_Rect dstrect = {(int) posicion.getX(),
						(int) posicion.getY(),
						JUGADOR_SRC_ANCHO,
						JUGADOR_SRC_ALTO};

	SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
    colorShip(srcrect, dstrect);

    helperAbove->render(estadoJugador.helper1, coloresRender, estadoJugador.presente);
    helperBelow->render(estadoJugador.helper2, coloresRender, estadoJugador.presente);

    colorGlow();

	srcrect = {JUGADOR_SRC_ANCHO * 2 * (contadorVelocidadY < -10) + JUGADOR_SRC_ANCHO * 4 * (contadorVelocidadY > 10),
			   0, JUGADOR_SRC_ANCHO, JUGADOR_SRC_ALTO};
	SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
    SDL_SetTextureColorMod(textura, 255, 255, 255);
}


void JugadorVista::colorShip(SDL_Rect srcrect, SDL_Rect dstrect) {
    for (auto & i : coloresRender.base) {
        srcrect.y += JUGADOR_SRC_ALTO;
        SDL_SetTextureColorMod(textura, i[0], i[1], i[2]);
        SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
    }
}


void JugadorVista::colorGlow() {
	contador++;
    std::array<int, 3> color = coloresRender.getColorGlow(contador);
	SDL_SetTextureColorMod(textura, color[0], color[1], color[2]);
}

int JugadorVista::getContador() const {
	return contador;
}
