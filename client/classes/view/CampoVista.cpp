#include <string>
#include "CampoVista.h"
#include "../GraphicRenderer.h"
#include "../../../commons/utils/Log.h"
#include "../../../commons/protocols/protocolo.h"

CampoVista::CampoVista(float velocidadMovilX) {
	CampoVista::gRenderer = GraphicRenderer::getInstance();
    CampoVista::velocidadNivel = velocidadMovilX;
    posX = 0;
	l->info("La vista del Campo fue creada correctamente.");
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
void CampoVista::render(EstadoTick estadoTick) {

    // Parche feo para que no se muestre un salto de fondo feo
    if (estadoTick.posX == 0) return;

    if (posX == 0) {
        posX = (float) estadoTick.posX;
    }

    posX += velocidadNivel;
    posX += ((float) estadoTick.posX - posX) / 120;

	// Renderizar todos los fondos
	for (FondoVista* fondo : fondos) {
        fondo->render(posX);
	}
}
