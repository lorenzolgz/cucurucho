//
// Created by javier on 18/7/20.
//

#include "EnemigoFinal1ExtVista.h"
#include "../../GeneradorDeTexturas.h"
#include "../../../../commons/utils/Utils.h"

const int CANT_MODULOS = 10;
const int CANT_POSICIONES = 90;

EnemigoFinal1ExtVista::EnemigoFinal1ExtVista() {
	this->gRenderer = GraphicRenderer::getInstance();
	GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
	this->textura = generadorDeTexturas->generarTextura("boss-ext.png");
	this->contador = 0;


	l->info("La vista de la extension del Enemigo Final 1 fue creada correctamente.");
}


void EnemigoFinal1ExtVista::render(EstadoEnemigo estadoEnemigo, Vector lock) {
	Vector posicion = Vector(estadoEnemigo.posicionX, estadoEnemigo.posicionY);
	this->lock = lock;

	if (posiciones.empty()) {
		inicializarPosiciones(posicion);
	}

	posiciones.push_front(posicion);
	if (posiciones.size() > CANT_POSICIONES) {
		posiciones.pop_back();
	}

	for (int i = 0; i < CANT_MODULOS; i++) {
		renderModulo(posicion, i);
	}

	contador++;
	l->debug("Vista de la extension del Enemigo Final 1: "+ posicion.getVector());
}

void EnemigoFinal1ExtVista::renderModulo(Vector posicionEstado, int i) {
	Vector posicion = posiciones[i * CANT_POSICIONES / CANT_MODULOS];

	posicion = posicion - (posicion - lock) / CANT_MODULOS * i;

	if (i > 2) i = 2;

	SDL_Rect srcrect = {ENEMIGO_FINAL1_EXT_SRC_ANCHO * i, 0, ENEMIGO_FINAL1_EXT_SRC_ANCHO, ENEMIGO_FINAL1_EXT_SRC_ALTO};
	SDL_Rect dstrect = {(int) posicion.getX(), (int) posicion.getY(), ENEMIGO_FINAL1_EXT_SRC_ANCHO, ENEMIGO_FINAL1_EXT_SRC_ALTO};

	if (i == 0) {
		srcrect.y += ENEMIGO_FINAL1_EXT_SRC_ALTO * (contador % 60 >= 30);
	}
	SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
}

void EnemigoFinal1ExtVista::inicializarPosiciones(Vector posicion) {
	for (int i = 0; i < CANT_POSICIONES; i++) {
		posiciones.push_back(posicion);
	}
}