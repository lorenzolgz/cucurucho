//
// Created by javier on 9/4/20.
//

#include "VentanaJuego.h"

VentanaJuego::VentanaJuego(SDL_Renderer *gRenderer, SDL_Rect rectVentana) {
	velocidad = 2;
	vista = new VentanaJuegoVista(gRenderer, rectVentana);
}

FondoVista * VentanaJuego::nuevoFondo(const std::string &fileName, float xOffset, int yFondo, float modVelocidad) {
	return vista->nuevoFondo(fileName, xOffset, yFondo, modVelocidad);
}

/*
 * Renderizar todos los fondos. A cada uno se le envia el renderer y ellos mismos
 * actualizan sus coordenadas en la ventana.
 */
void VentanaJuego::render() {
	vista->render(velocidad);
}
