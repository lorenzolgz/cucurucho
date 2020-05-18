#include <string>
#include "CampoVista.h"
#include "../GraphicRenderer.h"
#include "../Log.h"

CampoVista::CampoVista(int ancho, int alto, int inicioEnEjeY) {
	CampoVista::gRenderer = GraphicRenderer::getInstance();
	CampoVista::posCampo = { 0, inicioEnEjeY, ancho, alto };
	l->info("La vista del Campo fue creada correctamente.");
}

FondoVista * CampoVista::nuevoFondo(const std::string &fileName, float xOffset, int yFondo, float modVelocidad, float* velocidadMovilX) {
	FondoVista* fondo = new FondoVista(fileName, xOffset, yFondo, modVelocidad, velocidadMovilX);
	fondos.push_front(fondo);
	return fondo;
}

/*
 * Renderizar todos los fondos. A cada uno se le envia el renderer y ellos mismos
 * actualizan sus coordenadas en el campo.
 */
void CampoVista::render() {
	// Cambia el viewport por el que tiene asignado.
	SDL_RenderSetViewport(gRenderer, &posCampo);

	// Renderizar todos los fondos
	for (FondoVista* fondo : fondos) {
		fondo->render();
	}
}
