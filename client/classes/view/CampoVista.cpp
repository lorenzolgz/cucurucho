#include <string>
#include "CampoVista.h"
#include "../GraphicRenderer.h"
#include "../../../commons/utils/Log.h"
#include "../../../commons/protocols/protocolo.h"

CampoVista::CampoVista(float velocidadMovilX, int numeroNivel) {
	CampoVista::gRenderer = GraphicRenderer::getInstance();
    CampoVista::velocidadNivel = velocidadMovilX;
    CampoVista::numeroNivel = numeroNivel;
    posX = 0;
    ultimoTick = 0;
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

    // Para evitar un salto feo apenas se conecta el cliente al nuevo nivel
    if (estadoTick.posX == 0 || estadoTick.numeroNivel != numeroNivel) return;

    // Para el caso donde se desencole un mensaje "muy viejo"
    if (estadoTick.posX >= ultimoTick) {
        ultimoTick = estadoTick.posX;
    }

    if (posX == 0) {
        posX = (float) ultimoTick;
    }

    posX += velocidadNivel;

    posX += ((float) ultimoTick - posX) / 120;

	// Renderizar todos los fondos
	for (FondoVista* fondo : fondos) {
        fondo->render(posX);
	}
}

int CampoVista::getNumeroNivel() const {
	return numeroNivel;
}
