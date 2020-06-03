//
// Created by javier on 29/5/20.
//

#include "ManagerVista.h"
#include "../GraphicRenderer.h"
#include "NivelIntermedioVista.h"
#include "Enemigo1Vista.h"
#include "../../../commons/utils/Constantes.h"
#include <utility>

ManagerVista::ManagerVista(JugadorVista* jugador, std::vector<NivelConfiguracion *>  listNiveles, int nivelActual, int ancho, int alto)
        : jugador(jugador), listNiveles(std::move(listNiveles)), nivelActual(nivelActual), alto(alto), ancho(ancho) {
    hud = HudVista();
    posX = 0;
    campoVista = nullptr;
    enemigo1Vista = Enemigo1Vista();
    enemigo2Vista = Enemigo2Vista();
    cambiarNivel(nivelActual);
}

void ManagerVista::render(EstadoTick estadoTick) {
    hud.render();

    SDL_Rect posCampo = { 0, HUD_SRC_ALTO, ancho, alto };
    SDL_RenderSetViewport(GraphicRenderer::getInstance(), &posCampo);
    campoVista->render();
    renderEnemigos(estadoTick.estadosEnemigos);
}

bool ManagerVista::cambiarNivel(int nivel) {
    if (nivel < 0 || nivel >= listNiveles.size()) {
        return false;
    }
    nivelActual = nivel;

    delete campoVista;
    campoVista = new CampoVista();
    for (FondoConfiguracion * f : listNiveles.at(nivel)->getFondos()) {
        campoVista->nuevoFondo(f->getArchivo(), 0, 0, f->getVelocidad(), &posX);
    }
    posX = listNiveles.at(nivel)->getVelocidad();
    return true;
}

void ManagerVista::renderNivelIntermedio() {
    NivelIntermedioVista(listNiveles.at(nivelActual)->getFinalNivel()).render();
}

void ManagerVista::renderEnemigos(EstadoEnemigo *estadosEnemigos) {
    int n = 0;
    // TODO: Sacar limite enemigos
    while (n < MAX_ENEMIGOS && estadosEnemigos[++n].clase != 0);

    for (int i = 0; i < n; i++) {
        switch (estadosEnemigos[i].clase) {
            case 1:
                enemigo1Vista.render(estadosEnemigos[i]);
                break;
            case 2:
                enemigo2Vista.render(estadosEnemigos[i]);
        }
    }
}
