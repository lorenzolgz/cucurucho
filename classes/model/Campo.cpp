//
// Created by javier on 9/4/20.
//

#include <algorithm>
#include "Campo.h"
#include "Enemigo1.h"
#include "../Log.h"
#include "Enemigo2.h"

Campo::Campo(SDL_Renderer *gRenderer, SDL_Rect rectCampo, Jugador* jugador) {
	velocidad = 2;

	Campo::jugador = jugador;
	enemigos.push_back(new Enemigo1(gRenderer, 825, 420));
	enemigos.push_back(new Enemigo2(gRenderer, 600, 45));

	vista = new CampoVista(gRenderer, rectCampo);
}

FondoVista * Campo::nuevoFondo(const std::string &fileName, float xOffset, int yFondo, float modVelocidad) {
	return vista->nuevoFondo(fileName, xOffset, yFondo, modVelocidad);
}

/*
 * Renderizar todos los fondos. A cada uno se le envia el renderer y ellos mismos
 * actualizan sus coordenadas en el campo.
 */
void Campo::tick() {
	vista->render(velocidad);
	std::for_each(enemigos.begin(), enemigos.end(), [](Ticker* t) { t->tick(); });
	jugador->tick();
}
