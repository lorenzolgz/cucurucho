#include "JugadorVista.h"
#include "../../../commons/utils/Utils.h"
#include "../../../commons/utils/Log.h"
#include "../GeneradorDeTexturas.h"
#include "../GraphicRenderer.h"
#include "HelperVista.h"

JugadorVista::JugadorVista(ColoresJugador colores) {
	JugadorVista::gRenderer = GraphicRenderer::getInstance();
    GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
    JugadorVista::textura = generadorDeTexturas->generarTextura("player.png");
	JugadorVista::contador = 0;
	JugadorVista::contadorVelocidadY = 0;
    JugadorVista::colores = colores;
    helperAbove = new HelperVista(colores);
    helperBelow = new HelperVista(colores);
	l->info("La vista del jugador fue creada correctamente.");
}


void JugadorVista::calcularVelocidadY(Vector nuevaPosicion) {
    if ((posicion - nuevaPosicion).getY() > 1) {
        contadorVelocidadY += contadorVelocidadY < 14;
    } else if ((posicion - nuevaPosicion).getY() < -1) {
        contadorVelocidadY -= contadorVelocidadY > -14;
    } else {
        contadorVelocidadY += (contadorVelocidadY < 0) - (contadorVelocidadY > 0);
    }
}


//void JugadorVista::render(Vector nuevaPosicion, Vector posHelper1, float argHelper1, Vector posHelper2, float argHelper2) {
void JugadorVista::render(struct EstadoJugador estadoJugador) {
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

    helperAbove->render(estadoJugador.helper1);
    helperBelow->render(estadoJugador.helper2);

    // TODO cambiar glow por black and white
    if(estadoJugador.presente){
        colorGlow();
        std::cout << "El jugador que en Y tiene: " << estadoJugador.posicionY << " esta presente" << std::endl;
    } else {
        std::cout << "El jugador que en Y tiene: " << estadoJugador.posicionY << " (NO) esta presente" << std::endl;
    }

	srcrect = {JUGADOR_SRC_ANCHO * 2 * (contadorVelocidadY < -10) + JUGADOR_SRC_ANCHO * 4 * (contadorVelocidadY > 10),
			   0, JUGADOR_SRC_ANCHO, JUGADOR_SRC_ALTO};
	SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
    SDL_SetTextureColorMod(textura, 255, 255, 255);
}


void JugadorVista::colorShip(SDL_Rect srcrect, SDL_Rect dstrect) {
    for (auto & i : colores.base) {
        srcrect.y += JUGADOR_SRC_ALTO;
        SDL_SetTextureColorMod(textura, i[0], i[1], i[2]);
        SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
    }
}


void JugadorVista::colorGlow() {
	contador++;
    std::array<int, 3> color = colores.getColorGlow(contador);
	SDL_SetTextureColorMod(textura, color[0], color[1], color[2]);
}

int JugadorVista::getContador() const {
	return contador;
}
