#include "VentanaJuegoVista.h"

VentanaJuegoVista::VentanaJuegoVista(SDL_Renderer *gRenderer, SDL_Rect rectVentana) {
	VentanaJuegoVista::gRenderer = gRenderer;
	VentanaJuegoVista::posVentana = rectVentana;
}

FondoVista * VentanaJuegoVista::nuevoFondo(const std::string &fileName, float xOffset, int yFondo, float modVelocidad) {
	FondoVista* fondo = new FondoVista(gRenderer, fileName, xOffset, yFondo, modVelocidad);
	fondos.push_front(fondo);
	return fondo;
}

/*
 * Renderizar todos los fondos. A cada uno se le envia el renderer y ellos mismos
 * actualizan sus coordenadas en la ventana.
 */
void VentanaJuegoVista::render(float velocidad) {
	// Cambia el viewport por el que tiene asignado.
	SDL_RenderSetViewport(gRenderer, &posVentana);

	// Renderizar todos los fondos
	for (FondoVista* fondo : fondos) {
		fondo->render(gRenderer, velocidad);
	}
}
