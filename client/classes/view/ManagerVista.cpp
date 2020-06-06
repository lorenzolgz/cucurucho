//
// Created by javier on 29/5/20.
//

#include "ManagerVista.h"
#include "../GraphicRenderer.h"
#include "NivelIntermedioVista.h"
#include "Enemigo1Vista.h"
#include "../../../commons/utils/Constantes.h"
#include <utility>

ManagerVista::ManagerVista(struct InformacionNivel infoNivel, int nivelActual, int ancho, int alto)
        : informacionNivel(infoNivel), nivelActual(nivelActual), alto(alto), ancho(ancho) {
    hud = HudVista();
    posX = 0;
    campoVista = nullptr;
    enemigo1Vista = Enemigo1Vista();
    enemigo2Vista = Enemigo2Vista();
}

void ManagerVista::render(EstadoTick estadoTick) {
    hud.render();

    SDL_Rect posCampo = { 0, HUD_SRC_ALTO, ancho, alto };
    SDL_RenderSetViewport(GraphicRenderer::getInstance(), &posCampo);
    campoVista->render();
    renderEnemigos(estadoTick.estadosEnemigos);
}


void ManagerVista::setInformacionNivel(InformacionNivel &informacionNivel) {
    ManagerVista::informacionNivel = informacionNivel;

    campoVista = new CampoVista();
    for (InformacionFondo & f : informacionNivel.informacionFondo) {
        if (f.pFondo[0] == '\0') continue;
        campoVista->nuevoFondo(f.pFondo, 0, 0, f.pVelocidad, &posX);
    }

    // TODO: VELOCIDAD DEL NIVEL.
    posX = 2;
}


void ManagerVista::renderNivelIntermedio() {
    NivelIntermedioVista(informacionNivel.informacionFinNivel).render();
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