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

    jugadores.push_back(new JugadorVista(COLORES_AZUL));
    jugadores.push_back(new JugadorVista(COLORES_ROJO));
    jugadores.push_back(new JugadorVista(COLORES_ROSA));
    jugadores.push_back(new JugadorVista(COLORES_TURQUESA));

}

void ManagerVista::render(EstadoTick estadoTick) {
    hud.render();

    SDL_Rect posCampo = { 0, HUD_SRC_ALTO, ancho, alto };
    SDL_RenderSetViewport(GraphicRenderer::getInstance(), &posCampo);
	if (campoVista == nullptr) {
        return;
	} // !!!! TODO javi
	campoVista->render();

    renderEnemigos(estadoTick.estadosEnemigos);

    for (int i = 0; i < MAX_JUGADORES; i++) {
        jugadores[i]->render(estadoTick.estadosJugadores[i]);
    }
}


void ManagerVista::setInformacionNivel(InformacionNivel informacionNivel) {
    if (ManagerVista::informacionNivel.numeroNivel == informacionNivel.numeroNivel) {
        return;
    }

    if (informacionNivel.numeroNivel > 1) {
        this->renderNivelIntermedio();
        SDL_RenderPresent(GraphicRenderer::getInstance());
        SDL_Delay(2000);
    }

    ManagerVista::informacionNivel = informacionNivel;

    campoVista = new CampoVista();
    for (InformacionFondo & f : informacionNivel.informacionFondo) {
    	// Continuar si se cuenta con menos fondos que MAX_FONDOS(constante fija para pasar mensaje)
        if (f.pFondo[0] == '\0') {
        	continue;
        }
        campoVista->nuevoFondo(f.pFondo, 0, 0, f.pVelocidad, &posX);
    }

    posX = informacionNivel.velocidad;
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
