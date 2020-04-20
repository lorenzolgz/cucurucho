//
// Created by javier on 9/4/20.
//

#include "Campo.h"

Campo::Campo(SDL_Renderer *gRenderer, SDL_Rect rectCampo, Jugador* jugador) {
	velocidad = 2;
	Campo::jugador = jugador;
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
	jugador->tick();
}
