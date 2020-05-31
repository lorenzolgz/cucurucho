//
// Created by javier on 29/5/20.
//

#include "ManagerVista.h"

#include <utility>

ManagerVista::ManagerVista(JugadorVista* jugador, std::vector<NivelConfiguracion *>  listNiveles, int nivelActual, int ancho, int alto)
        : jugador(jugador), listNiveles(std::move(listNiveles)), nivelActual(nivelActual), alto(alto), ancho(ancho) {
    hud = HudVista();
    posX = 0;
    campoVista = nullptr;
    cambiarNivel(nivelActual);
}

void ManagerVista::render() {
    campoVista->render();
}

void ManagerVista::cambiarNivel(int nivel) {
    nivelActual = nivel;

    delete campoVista;
    campoVista = new CampoVista(ancho, alto, HUD_SRC_ALTO);
    for (FondoConfiguracion * f : listNiveles.at(nivel)->getFondos()) {
        campoVista->nuevoFondo(f->getArchivo(), 0, 0, f->getVelocidad(), &posX);
    }
    posX = listNiveles.at(nivel)->getVelocidad();
}

