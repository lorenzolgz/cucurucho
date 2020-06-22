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
    primerNivel = true;

    jugadores.push_back(new JugadorVista(COLORES_AZUL));
    jugadores.push_back(new JugadorVista(COLORES_ROJO));
    jugadores.push_back(new JugadorVista(COLORES_ROSA));
    jugadores.push_back(new JugadorVista(COLORES_TURQUESA));

}

void ManagerVista::render(EstadoTick estadoTick, EstadoLogin estadoLogin, std::string username) {
    hud.render(estadoLogin, username);

    SDL_Rect posCampo = { 0, HUD_SRC_ALTO, ancho, alto };
    SDL_RenderSetViewport(GraphicRenderer::getInstance(), &posCampo);
	if (campoVista == nullptr) {
	    if (estadoLogin.estadoLogin == LOGIN_ESPERAR || estadoLogin.estadoLogin == LOGIN_COMENZAR) {
            renderEspera(estadoLogin);
	    }
        return;
	} // TODO patch para race conditions
	campoVista->render();

    renderEnemigos(estadoTick.estadosEnemigos);

    for (int i = 0; i < MAX_JUGADORES; i++) {
        jugadores[i]->render(estadoTick.estadosJugadores[i]);
    }

    posCampo = { 0, 0, ancho, alto };
    SDL_RenderSetViewport(GraphicRenderer::getInstance(), &posCampo);
}


void ManagerVista::setInformacionNivel(InformacionNivel informacionNivel) {
    if (ManagerVista::informacionNivel.numeroNivel == informacionNivel.numeroNivel) {
        return;
    }

    if (!primerNivel) {
        this->renderNivelIntermedio();
        SDL_RenderPresent(GraphicRenderer::getInstance());
        SDL_Delay(TIMEOUT_PROXIMO_NIVEL * 1000);
    }

    primerNivel = false;

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


// Funcion para generar el estado del jugador y los helpers a partir de un vector posicion.
// Utilizado para la pantalla de espera.
struct EstadoJugador generarEstadoJugador(Vector posicion) {
    struct EstadoJugador estadoJugador;
    estadoJugador.posicionX = posicion.getX();
    estadoJugador.posicionY = posicion.getY();
    estadoJugador.presente = true;

    // Sin helpers
    Vector posicionHelper1 = posicion + Vector(-10000, -10000);
    estadoJugador.helper1.posicionX = posicionHelper1.getX();
    estadoJugador.helper1.posicionY = posicionHelper1.getY();

    Vector posicionHelper2 = posicion + Vector(-10000, -10000);
    estadoJugador.helper2.posicionX = posicionHelper2.getX();
    estadoJugador.helper2.posicionY = posicionHelper2.getY();

    return estadoJugador;
}


void ManagerVista::renderEsperaJugador(JugadorVista* jugador, char* nombre, int indice, int colorTexto) {
    Vector posicionJugadorBase = Vector(ancho / 3, alto * 1 / 12);
    Vector posicionNombreBase = Vector(ancho * 7 / 15, alto * 1 / 12 + JUGADOR_SRC_ALTO / 3);
    Vector distancia_y = Vector(0, alto / 7);
    struct EstadoJugador estado = generarEstadoJugador(posicionJugadorBase + (distancia_y * indice));

    if (strlen(nombre) > 0) {
        estado.presente = true;
        TextoVista::eRender(std::string(nombre), posicionNombreBase + (distancia_y * indice), colorTexto, ALINEACION_IZQUIERDA);
    } else {
        estado.presente = false;
    }
    jugador->render(estado);
}


void ManagerVista::renderEspera(struct EstadoLogin estadoLogin) {
    renderEsperaJugador(jugadores[0], estadoLogin.jugador1, 0, TEXTO_COLOR_AZUL);
    renderEsperaJugador(jugadores[1], estadoLogin.jugador2, 1, TEXTO_COLOR_ROJO);
    renderEsperaJugador(jugadores[2], estadoLogin.jugador3, 2, TEXTO_COLOR_ROSA);
    renderEsperaJugador(jugadores[3], estadoLogin.jugador4, 3, TEXTO_COLOR_TURQUESA);

    if (estadoLogin.estadoLogin == LOGIN_ESPERAR) {
        TextoVista::eRender(std::string("ESPERANDO JUGADORES..."), Vector(ancho / 2, alto * 5 / 7), TEXTO_COLOR_NARANJA, ALINEACION_CENTRO);
    } else if (estadoLogin.estadoLogin == LOGIN_COMENZAR) {
        TextoVista::eRender(std::string("COMENZANDO PARTIDA..."), Vector(ancho / 2, alto * 5 / 7), TEXTO_COLOR_VERDE, ALINEACION_CENTRO);
    }
}