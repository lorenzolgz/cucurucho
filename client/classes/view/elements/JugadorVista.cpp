#include "JugadorVista.h"
#include "../../../../commons/utils/Utils.h"
#include "../../../../commons/utils/Log.h"
#include "../../GeneradorDeTexturas.h"
#include "../../GraphicRenderer.h"
#include "HelperVista.h"
#include "../../Audio.h"

JugadorVista::JugadorVista(ColoresJugador colores) {
	JugadorVista::gRenderer = GraphicRenderer::getInstance();
    GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
    JugadorVista::textura = generadorDeTexturas->generarTextura("player.png");
    JugadorVista::texturaEnergia = generadorDeTexturas->generarTextura("lifebar.png");
	JugadorVista::contador = 0;
	JugadorVista::contadorVelocidadY = 0;
    JugadorVista::colores = colores;

//  USO EFECTOS DE SONIDO: Creo instancia de efecto que quiero y cuando la necesito audio->play(volumen)
    Audio *audio = new Audio();
    JugadorVista::audioPerder = audio->generarEfecto("sfx-25.wav");
    JugadorVista::audioRevivir = audio->generarEfecto("sfx-07.wav");

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
    posicion = nuevaPosicion;
}


void JugadorVista::render(struct EstadoJugador estadoJugador) {
    contador++;

    if (!deberiaRenderizar(estadoJugador)) return;

    calcularVelocidadY(Vector(estadoJugador.posicionX, estadoJugador.posicionY));
    setColores(estadoJugador);

	SDL_Rect srcrect = {JUGADOR_SRC_ANCHO + JUGADOR_SRC_ANCHO * 2 * (contadorVelocidadY < -10) + JUGADOR_SRC_ANCHO * 4 * (contadorVelocidadY > 10),
						0, JUGADOR_SRC_ANCHO, JUGADOR_SRC_ALTO};

	SDL_Rect dstrect = {(int) posicion.getX(),
						(int) posicion.getY(),
						JUGADOR_SRC_ANCHO,
						JUGADOR_SRC_ALTO};

    renderShip(srcrect, dstrect);

    helperAbove->render(estadoJugador.helper1, coloresRender, estadoJugador);
    helperBelow->render(estadoJugador.helper2, coloresRender, estadoJugador);

    renderGlow(srcrect, dstrect);

    renderLifebar(estadoJugador.energia);
}


void JugadorVista::renderShip(SDL_Rect srcrect, SDL_Rect dstrect) {
    SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
    for (auto & i : coloresRender.base) {
        srcrect.y += JUGADOR_SRC_ALTO;
        SDL_SetTextureColorMod(textura, i[0], i[1], i[2]);
        SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
    }
    SDL_SetTextureColorMod(textura, 255, 255, 255);
}


void JugadorVista::renderGlow(SDL_Rect srcrect, SDL_Rect dstrect) {
    std::array<int, 3> color = coloresRender.getColorGlow(contador);
	SDL_SetTextureColorMod(textura, color[0], color[1], color[2]);

    srcrect.x -= JUGADOR_SRC_ANCHO;
    SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
    SDL_SetTextureColorMod(textura, 255, 255, 255);
}


void JugadorVista::renderLifebar(int energia) {
    SDL_Rect srcrect = {0, 0, BARRA_VIDA_SRC_ANCHO, BARRA_VIDA_SRC_ALTO};
    SDL_Rect dstrect = {(int) posicion.getX() + JUGADOR_SRC_ANCHO / 10,
                        (int) posicion.getY() + JUGADOR_SRC_ALTO + BARRA_VIDA_SRC_ALTO,
                        BARRA_VIDA_SRC_ANCHO * energia / 100, BARRA_VIDA_SRC_ALTO};

    std::array<int, 3> color = coloresRender.base[0];
    SDL_SetTextureColorMod(texturaEnergia, color[0], color[1], color[2]);

    SDL_RenderCopy(gRenderer, texturaEnergia, &srcrect, &dstrect);

    SDL_SetTextureColorMod(texturaEnergia, 255, 255, 255);

}


bool JugadorVista::deberiaRenderizar(struct EstadoJugador estadoJugador) {
    if (estadoJugador.estaMuerto) {
        return false;
    }

    return !(estadoJugador.esInvencible && contador % 4 >= 2);
}

void JugadorVista::setColores(EstadoJugador estadoJugador) {
    if (estadoJugador.presente) {
        coloresRender = colores;
        JugadorVista::textura = GeneradorDeTexturas::getInstance()->generarTextura("player.png");
    } else {
        coloresRender = COLORES_GRIS;
        JugadorVista::textura = GeneradorDeTexturas::getInstance()->generarTextura("player-g.png");
    }
}
