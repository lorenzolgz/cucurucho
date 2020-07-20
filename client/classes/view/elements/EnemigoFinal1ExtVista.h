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
	bool estadoEnRango(EstadoEnemigo estadoEnemigo);

private:
	SDL_Renderer* gRenderer;
	SDL_Texture* textura;
	std::deque<Vector> posiciones;
	Vector lock;
	Vector posicion;
	int contador;

	void renderModulo(int i);
	void inicializarPosiciones();
};


#endif //CUCURUCHO_ENEMIGOFINAL1EXTVISTA_H
