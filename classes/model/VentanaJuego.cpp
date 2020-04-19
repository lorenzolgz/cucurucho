//
// Created by javier on 9/4/20.
//

#include "VentanaJuego.h"

Fondo * VentanaJuego::nuevoFondo(const std::string &fileName, float xOffset, int yFondo, float modVelocidad) {
    auto* fondo = new Fondo(gRenderer, fileName, xOffset, yFondo, modVelocidad);
    fondos.push_front(fondo);
    return fondo;
}

/*
 * Renderizar todos los fondos. A cada uno se le envia el renderer y ellos mismos
 * actualizan sus coordenadas en la ventana.
 */
void VentanaJuego::render() {
    // Cambia el viewport por el que tiene asignado.
    SDL_RenderSetViewport(gRenderer, &posVentana);

    // No se usa. ¿Se queda?
    posX -= velocidad;

    // Renderizar todos los fondos
    for (auto fondo : fondos) {
        fondo->render(gRenderer, velocidad);
    }
}

VentanaJuego::VentanaJuego(SDL_Renderer *gRenderer, SDL_Rect rectVentana) {
    posX = 0;
    velocidad = 2;
    VentanaJuego::posVentana = rectVentana;
    VentanaJuego::gRenderer = gRenderer;
}
