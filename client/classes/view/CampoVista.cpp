#include <string>
#include "CampoVista.h"
#include "../GraphicRenderer.h"
#include "../Log.h"

CampoVista::CampoVista() {
	CampoVista::gRenderer = GraphicRenderer::getInstance();
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

	// Renderizar todos los fondos
	for (FondoVista* fondo : fondos) {
		fondo->render();
	}
}
