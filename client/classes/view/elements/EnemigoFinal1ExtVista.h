//
// Created by javier on 18/7/20.
//

#ifndef CUCURUCHO_ENEMIGOFINAL1EXTVISTA_H
#define CUCURUCHO_ENEMIGOFINAL1EXTVISTA_H


#include <SDL_render.h>
#include "../../../../commons/protocols/protocolo.h"
#include "../../../../commons/utils/Vector.h"
#include <deque>

const int ENEMIGO_FINAL1_EXT_SRC_ANCHO = 42;
const int ENEMIGO_FINAL1_EXT_SRC_ALTO = 42;

class EnemigoFinal1ExtVista {
public:
	EnemigoFinal1ExtVista();
	void render(EstadoEnemigo estadoEnemigo, Vector lock);

private:
	SDL_Renderer* gRenderer;
	SDL_Texture* textura;
	std::deque<Vector> posiciones;
	Vector lock;
	int contador;

	void renderModulo(Vector posicion, int i);
	void inicializarPosiciones(Vector posicion);
};


#endif //CUCURUCHO_ENEMIGOFINAL1EXTVISTA_H
