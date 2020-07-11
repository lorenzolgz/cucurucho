#include "EnemigoFinal1Vista.h"
#include "../GraphicRenderer.h"
#include "../GeneradorDeTexturas.h"
#include "../../../commons/utils/Vector.h"

EnemigoFinal1Vista::EnemigoFinal1Vista() {
	this->gRenderer = GraphicRenderer::getInstance();
	GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
	this->textura = generadorDeTexturas->generarTextura("enemy02.png");
	l->info("La vista del Enemigo Final 1 fue creada correctamente.");
}

void EnemigoFinal1Vista::render(EstadoEnemigo estadoEnemigo) {
	Vector posicion = Vector(estadoEnemigo.posicionX, estadoEnemigo.posicionY);
	SDL_Rect srcrect = {0, 0 + ENEMIGO_FINAL1_SRC_ALTO, ENEMIGO_FINAL1_SRC_ANCHO, ENEMIGO_FINAL1_SRC_ALTO};
	SDL_Rect dstrect = {(int) posicion.getX(), (int) posicion.getY(), ENEMIGO_FINAL1_SRC_ANCHO, ENEMIGO_FINAL1_SRC_ALTO};

	SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
	l->debug("Vista del Enemigo 02: "+ posicion.getVector());
}
