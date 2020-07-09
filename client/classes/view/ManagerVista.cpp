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
    velocidadNivel = 0;
    campoVista = nullptr;
    enemigo1Vista = Enemigo1Vista();
    enemigo2Vista = Enemigo2Vista();
    primerNivel = true;

    for (int i = 0; i < MAX_JUGADORES; i++) {
        jugadores.push_back(new JugadorVista(COLORES_JUGADOR_ARR[i]));
    }

}

void ManagerVista::render(EstadoTick estadoTick, EstadoLogin estadoLogin, std::string username) {
	// Render Hud
	struct EstadoJugador estadoJugadorPropio;
	int i;
	for (i = 0; i < MAX_JUGADORES; i++) {
		EstadoJugador estadoJugador = estadoTick.estadosJugadores[i];
		// validar presente? !!!! probablemente no se de nunca que no este presente
		if (i == estadoLogin.nroJugador - 1) {
			estadoJugadorPropio = estadoJugador;
			break;
		}
	}
	// !!!!
	if (i > MAX_JUGADORES) {
		l->error("!!!! no tendria que pasar: " + std::to_string(i));
		exit(3);
	}
	hud.setPuntajeVida(estadoJugadorPropio.puntajeVida);
    hud.render(estadoLogin, username);

    // Render Campo
    SDL_Rect posCampo = { 0, HUD_SRC_ALTO, ancho, alto };
    SDL_RenderSetViewport(GraphicRenderer::getInstance(), &posCampo);
	if (campoVista == nullptr) {
	    if (estadoLogin.estadoLogin == LOGIN_ESPERAR || estadoLogin.estadoLogin == LOGIN_COMENZAR) {
            renderEspera(estadoLogin);
	    }
        return;
	} // TODO patch para race conditions
    campoVista->render(estadoTick);

	// Render resto
    renderEnemigos(estadoTick.estadosEnemigos);

    renderJugadores(estadoTick, estadoLogin);

    posCampo = { 0, 0, ancho, alto };
    SDL_RenderSetViewport(GraphicRenderer::getInstance(), &posCampo);
}


void ManagerVista::setInformacionNivel(InformacionNivel informacionNivel, EstadoTick tick) {
    if (ManagerVista::informacionNivel.numeroNivel == informacionNivel.numeroNivel && tick.numeroNivel >= 0) {
        return;
    }

    if (!primerNivel) {
        this->renderNivelIntermedio();
        SDL_RenderPresent(GraphicRenderer::getInstance());
        SDL_Delay(TIMEOUT_PROXIMO_NIVEL * 1000);
    }

    primerNivel = false;

    ManagerVista::informacionNivel = informacionNivel;

    velocidadNivel = informacionNivel.velocidad;
    campoVista = new CampoVista(velocidadNivel, informacionNivel.numeroNivel);

    for (InformacionFondo f : informacionNivel.informacionFondo) {
    	// Continuar si se cuenta con menos fondos que MAX_FONDOS(constante fija para pasar mensaje)
        if (f.pFondo[0] == '\0') {
        	continue;
        }
        campoVista->nuevoFondo(f.pFondo, 0, 0, f.pVelocidad);
    }
}


void ManagerVista::renderNivelIntermedio() {
    NivelIntermedioVista(informacionNivel.informacionFinNivel).render();
}


void ManagerVista::renderEnemigos(std::list<EstadoEnemigo> estadosEnemigos) {
    int n = 0;


    for (EstadoEnemigo estadoEnemigo: estadosEnemigos) {
        switch (estadoEnemigo.clase) {
            case 1:
                enemigo1Vista.render(estadoEnemigo);
                break;
            case 2:
                enemigo2Vista.render(estadoEnemigo);
        }
    }
}


void ManagerVista::renderJugadores(EstadoTick estadoTick, EstadoLogin estadoLogin) {

    // Primero se renderizan los jugadores desconectados
    for (int i = 0; i < MAX_JUGADORES; i++) {
        if (!estadoTick.estadosJugadores[i].presente) {
            jugadores[i]->render(estadoTick.estadosJugadores[i]);
        }
    }

    // Luego se renderizan los jugadores presentes que no sea el propio del usuario/cliente
    for (int i = 0; i < MAX_JUGADORES; i++) {
        if (estadoTick.estadosJugadores[i].presente && (estadoLogin.nroJugador-1) != i) {
            jugadores[i]->render(estadoTick.estadosJugadores[i]);
        }
    }

    // Finalmente, se renderiza el jugador del propio usuario/cliente
    jugadores[estadoLogin.nroJugador-1]->render(estadoTick.estadosJugadores[estadoLogin.nroJugador-1]);
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


void ManagerVista::renderEsperaJugador(JugadorVista* jugador, char* nombre, int indice, int colorTexto, int cantJugadores) {
    Vector posicionJugadorBase = Vector(ancho / 3, alto * 1 / 12);
    Vector posicionNombreBase = Vector(ancho * 7 / 15, alto * 1 / 12 + JUGADOR_SRC_ALTO / 3);
    Vector distancia_y = Vector(0, alto * 7 / 12) / cantJugadores;
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
    for (int i = 0; i < estadoLogin.cantidadJugadores ; i++) {
        renderEsperaJugador(jugadores[i], estadoLogin.jugadores[i], i, i + 1, estadoLogin.cantidadJugadores);
    }

    if (estadoLogin.estadoLogin == LOGIN_ESPERAR) {
        TextoVista::eRender(std::string("ESPERANDO JUGADORES..."), Vector(ancho / 2, alto * 5 / 7), TEXTO_COLOR_NARANJA, ALINEACION_CENTRO);
    } else if (estadoLogin.estadoLogin == LOGIN_COMENZAR) {
        TextoVista::eRender(std::string("COMENZANDO PARTIDA..."), Vector(ancho / 2, alto * 5 / 7), TEXTO_COLOR_VERDE, ALINEACION_CENTRO);
    }
}