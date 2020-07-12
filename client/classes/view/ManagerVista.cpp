//
// Created by javier on 29/5/20.
//

#include "ManagerVista.h"
#include "../GraphicRenderer.h"
#include "NivelIntermedioVista.h"
#include "Enemigo1Vista.h"
#include "../../../commons/utils/Constantes.h"
#include "EnemigoFinal1Vista.h"
#include "ExplosionVista.h"
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

}

void ManagerVista::render(EstadoTick estadoTick, EstadoLogin estadoLogin, std::string username) {
	// Render Hud
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

    // Estos son valores dummies que no se usan
    estadoJugador.energia = 0;
    estadoJugador.cantidadVidas = 3;
    estadoJugador.esInvencible = false;

    // Sin esto no se renderiza el jugador.
    estadoJugador.estaMuerto = false;

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
        renderEsperaJugador((*jugadores)[i], estadoLogin.jugadores[i], i, i + 1, estadoLogin.cantidadJugadores);
    }

    if (estadoLogin.estadoLogin == LOGIN_ESPERAR) {
        TextoVista::eRender(std::string("ESPERANDO JUGADORES..."), Vector(ancho / 2, alto * 5 / 7), TEXTO_COLOR_NARANJA, ALINEACION_CENTRO);
    } else if (estadoLogin.estadoLogin == LOGIN_COMENZAR) {
        TextoVista::eRender(std::string("COMENZANDO PARTIDA..."), Vector(ancho / 2, alto * 5 / 7), TEXTO_COLOR_VERDE, ALINEACION_CENTRO);
    }
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