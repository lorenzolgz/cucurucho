//
// Created by camix on 4/5/20.
//

#include "NivelIntermedioVista.h"
#include "../GraphicRenderer.h"

NivelIntermedioVista::NivelIntermedioVista(int ancho, int alto, int inicioEnEjeY) {
    NivelIntermedioVista::gRenderer = GraphicRenderer::getInstance();
    NivelIntermedioVista::posCampo = { 0, inicioEnEjeY, ancho, alto };
    l.info("La vista del Nivel Intermedio fue creada correctamente.");

}

FondoVista* NivelIntermedioVista::nuevoFondo(const std::string &fileName, float xOffset, int yFondo) {
    NivelIntermedioVista::fondo = new FondoVista(fileName, xOffset, yFondo, 0);
    return fondo;
}

void NivelIntermedioVista::render() {
    SDL_RenderSetViewport(gRenderer, &posCampo);
    fondo->render(0);
}
