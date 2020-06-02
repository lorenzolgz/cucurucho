//
// Created by camix on 4/5/20.
//

#include "NivelIntermedioVista.h"
#include "../GraphicRenderer.h"
#include <string>

NivelIntermedioVista::NivelIntermedioVista(const std::string fondoFilename) {
    NivelIntermedioVista::gRenderer = GraphicRenderer::getInstance();
    nuevoFondo(fondoFilename);
    l->info("La vista del Nivel Intermedio fue creada correctamente.");
}

FondoVista* NivelIntermedioVista::nuevoFondo(const std::string &fileName) {
    NivelIntermedioVista::fondo = new FondoVista(fileName, 0, 0, 0);
    return fondo;
}

void NivelIntermedioVista::render() {
    fondo->render();
}
