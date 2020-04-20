#include <string>
#include "CampoVista.h"
#include "../GraphicRenderer.h"
#include "../Log.h"

CampoVista::CampoVista(SDL_Rect rectCampo) {
	CampoVista::gRenderer = GraphicRenderer::getInstance();
	CampoVista::posCampo = rectCampo;
	l.info("Campo created");
}

FondoVista * CampoVista::nuevoFondo(const std::string &fileName, float xOffset, int yFondo, float modVelocidad) {
	FondoVista* fondo = new FondoVista(fileName, xOffset, yFondo, modVelocidad);
	fondos.push_front(fondo);
	return fondo;
}

/*
 * Renderizar todos los fondos. A cada uno se le envia el renderer y ellos mismos
 * actualizan sus coordenadas en el campo.
 */
void CampoVista::render(float velocidad) {
	// Cambia el viewport por el que tiene asignado.
	SDL_RenderSetViewport(gRenderer, &posCampo);

	// Renderizar todos los fondos
	for (FondoVista* fondo : fondos) {
		fondo->render(velocidad);
	}
}
