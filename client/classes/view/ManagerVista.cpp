//
// Created by javier on 29/5/20.
//

#include "ManagerVista.h"
#include "../GraphicRenderer.h"
#include "NivelIntermedioVista.h"
#include "elements/Enemigo1Vista.h"
#include "../../../commons/utils/Constantes.h"
#include "elements/EnemigoFinal1Vista.h"
#include "elements/ExplosionVista.h"
#include <utility>

ManagerVista::ManagerVista(struct InformacionNivel infoNivel, int nivelActual, int ancho, int alto)
        : informacionNivel(infoNivel), nivelActual(nivelActual), alto(alto), ancho(ancho) {
    hud = new HudVista();
    velocidadNivel = 0;
    campoVista = nullptr;
    enemigo1Vista = new Enemigo1Vista();
	enemigo2Vista = new Enemigo2Vista();
	enemigoFinal1Vista = new EnemigoFinal1Vista();
    disparoJugadorVista = new DisparoJugadorVista();
    primerNivel = true;

	for (int i = 0; i < MAX_JUGADORES; i++) {
		jugadores->push_back(new JugadorVista(COLORES_JUGADOR_ARR[i]));
	}
	nivelIntermedioVista = new NivelIntermedioVista(jugadores, ancho, alto);

}

void ManagerVista::render(EstadoTick estadoTick, EstadoLogin estadoLogin, std::string username) {

	renderHud(estadoTick, estadoLogin, username);
	if (campoVista == nullptr || campoVista->getNumeroNivel() != estadoTick.numeroNivel || estadoTick.posX <= 1) {
	    if (estadoLogin.estadoLogin == LOGIN_ESPERAR || estadoLogin.estadoLogin == LOGIN_COMENZAR) {
            nivelIntermedioVista->renderEstadoLogin(estadoLogin);
	    } else {
			this->renderNivelIntermedio(estadoTick, estadoLogin, username);
	    }
        return;
	} // TODO patch para race conditions

	// Render Campo
	SDL_Rect posCampo = { 0, HUD_SRC_ALTO, ancho, alto };
	SDL_RenderSetViewport(GraphicRenderer::getInstance(), &posCampo);
    campoVista->render(estadoTick);

	// Render resto
    renderEnemigos(estadoTick.estadosEnemigos);
    renderDisparos(estadoTick.estadosDisparos);
    renderJugadores(estadoTick, estadoLogin);

    agregarExplosiones(estadoTick.estadosEnemigos, estadoTick.estadosDisparos);
    renderExplosiones();

    posCampo = { 0, 0, ancho, alto };
    SDL_RenderSetViewport(GraphicRenderer::getInstance(), &posCampo);
}


void ManagerVista::setInformacionNivel(InformacionNivel informacionNivel, EstadoTick tick) {
    if (ManagerVista::informacionNivel.numeroNivel == informacionNivel.numeroNivel && tick.numeroNivel >= 0) {
        return;
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


void ManagerVista::renderNivelIntermedio(EstadoTick estadoTick, EstadoLogin estadoLogin, std::string username) {
	if (!primerNivel) {
		renderHud(estadoTick, estadoLogin, username);
		nivelIntermedioVista->renderNivelIntermedio(estadoTick);
	}
}


void ManagerVista::renderEnemigos(std::list<EstadoEnemigo> estadosEnemigos) {

    for (EstadoEnemigo estadoEnemigo: estadosEnemigos) {
        switch (estadoEnemigo.clase) {
            case 1:
                enemigo1Vista->render(estadoEnemigo);
                break;
            case 2:
                enemigo2Vista->render(estadoEnemigo);
				break;
        	case 3:
				enemigoFinal1Vista->render(estadoEnemigo);
        }
    }
}


void ManagerVista::renderDisparos(std::list<EstadoDisparo> estadosDisparos) {
    for (EstadoDisparo estadoDisparo: estadosDisparos) {
      // Los ids positivos corresponden a JUGADORES, los negativos corresponden a ENEMIGOS
      if (estadoDisparo.nroJugador < 0) continue;

      disparoJugadorVista->render(estadoDisparo);
    }

}


void ManagerVista::renderJugadores(EstadoTick estadoTick, EstadoLogin estadoLogin) {

    // Primero se renderizan los jugadores desconectados
    for (int i = 0; i < MAX_JUGADORES; i++) {
        if (!estadoTick.estadosJugadores[i].presente) {
			(*jugadores)[i]->render(estadoTick.estadosJugadores[i]);
        }
    }

    // Luego se renderizan los jugadores presentes que no sea el propio del usuario/cliente
    for (int i = 0; i < MAX_JUGADORES; i++) {
        if (estadoTick.estadosJugadores[i].presente && (estadoLogin.nroJugador-1) != i) {
			(*jugadores)[i]->render(estadoTick.estadosJugadores[i]);
        }
    }

    // Finalmente, se renderiza el jugador del propio usuario/cliente
	(*jugadores)[estadoLogin.nroJugador-1]->render(estadoTick.estadosJugadores[estadoLogin.nroJugador-1]);
}


void ManagerVista::agregarExplosiones(std::list<EstadoEnemigo> enemigos, std::list<EstadoDisparo> disparos) {
    for (EstadoEnemigo e : enemigos) {
        if (e.energia > 0) continue;

        Vector pos = Vector(e.posicionX, e.posicionY);
        switch (e.clase) {
            case 1:
                explosiones.push_back(enemigo1Vista->nuevaExplosion(pos));
                break;
            case 2:
                explosiones.push_back(enemigo2Vista->nuevaExplosion(pos));
                break;
        }
    }

    for (EstadoDisparo d : disparos) {
        if (d.energia > 0) continue;

        Vector pos = Vector(d.posicionX, d.posicionY);
        switch (d.nroJugador) {
            default:
                explosiones.push_back(disparoJugadorVista->nuevaExplosion(pos));
        }

    }
}

void ManagerVista::renderExplosiones() {
    auto it = explosiones.begin();
    while (it != explosiones.end()) {
        (*it)->render();
        if (!(*it)->activa()) {
            delete (*it);
            it = explosiones.erase(it);
            l->debug("Explosion eliminada");
        } else {
            it++;
        }
    }
}

void ManagerVista::renderHud(EstadoTick estadoTick, EstadoLogin estadoLogin, std::string username) {
	struct EstadoJugador estadoJugadorPropio;
	int i;
	for (i = 0; i < MAX_JUGADORES; i++) {
		EstadoJugador estadoJugador = estadoTick.estadosJugadores[i];
		if (i == estadoLogin.nroJugador - 1) {
			estadoJugadorPropio = estadoJugador;
			break;
		}
	}

	hud->setCantidadVidasEnergiaPuntos(estadoJugadorPropio.cantidadVidas, estadoJugadorPropio.energia, estadoJugadorPropio.puntos);
	hud->render(estadoLogin, username);
}