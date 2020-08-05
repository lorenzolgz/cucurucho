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
#include "elements/EnemigoFinal1ExtVista.h"
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
	disparoHelperVista = new DisparoHelperVista();
    disparoEnemigoVista = new DisparoEnemigoVista();
    primerNivel = true;
    audio = Audio::getInstance();


	for (int i = 0; i < MAX_JUGADORES; i++) {
		jugadores->push_back(new JugadorVista(COLORES_JUGADOR_ARR[i]));
	}
	nivelIntermedioVista = new NivelIntermedioVista(jugadores, ancho, alto);

//    audio->generarMusica("audioPantallaInicio.mp3");
//    audio->playMusic("audioPantallaInicio.mp3");

}

void ManagerVista::render(EstadoTick estadoTick, EstadoLogin estadoLogin, std::string username) {

	renderHud(estadoTick, estadoLogin, username);
	if (campoVista == nullptr || (estadoTick.posX < 1 && !primerNivel)) {
	    if (estadoLogin.estadoLogin == LOGIN_ESPERAR || estadoLogin.estadoLogin == LOGIN_COMENZAR) {
            nivelIntermedioVista->renderEstadoLogin(estadoLogin);
	    } else {
			this->renderNivelIntermedio(estadoTick, estadoLogin, username);
	    }
        return;
	} // TODO patch para race conditions

	primerNivel = false;

	// Render Campo
	SDL_Rect posCampo = { 0, HUD_SRC_ALTO, ancho, alto };
	SDL_RenderSetViewport(GraphicRenderer::getInstance(), &posCampo);
    campoVista->render(estadoTick);

	// Render resto
    renderEnemigos(estadoTick.estadosEnemigos);

    renderDisparos(estadoTick.estadosDisparos);
    renderDisparosEnemigos(estadoTick.estadosDisparosEnemigos);

    renderJugadores(estadoTick, estadoLogin);

    agregarExplosiones(estadoTick.estadosEnemigos, estadoTick.estadosDisparos, estadoTick.estadosDisparosEnemigos,
    		estadoTick.estadosJugadores);

    renderExplosiones();

    posCampo = { 0, 0, ancho, alto };
    SDL_RenderSetViewport(GraphicRenderer::getInstance(), &posCampo);
}


void ManagerVista::setInformacionNivel(InformacionNivel informacionNivel, EstadoTick tick) {
    if (ManagerVista::informacionNivel.numeroNivel == informacionNivel.numeroNivel && tick.numeroNivel >= 0) {
        return;
    }

    ManagerVista::informacionNivel = informacionNivel;

    velocidadNivel = informacionNivel.velocidad;

    delete campoVista;
    campoVista = new CampoVista(velocidadNivel, informacionNivel.numeroNivel);

    for (InformacionFondo f : informacionNivel.informacionFondo) {
    	// Continuar si se cuenta con menos fondos que MAX_FONDOS(constante fija para pasar mensaje)
        if (f.pFondo[0] == '\0') {
        	continue;
        }
        campoVista->nuevoFondo(f.pFondo, 0, 0, f.pVelocidad);
    }

    delete enemigoFinal1Vista;
	enemigoFinal1Vista = new EnemigoFinal1Vista();

    std::string cancion = informacionNivel.audioNivel;
    audio->generarMusica(cancion);
    audio->playMusic(cancion);
}


void ManagerVista::renderNivelIntermedio(EstadoTick estadoTick, EstadoLogin estadoLogin, std::string username) {
	if (!primerNivel) {
		renderHud(estadoTick, estadoLogin, username);
		nivelIntermedioVista->renderNivelIntermedio(estadoTick);
	}
}


void ManagerVista::renderEnemigos(std::list<EstadoEnemigo> estadosEnemigos) {
	EstadoEnemigo enemigoFinal;
	enemigoFinal.clase = -1;

	std::list<EstadoEnemigo> extensionesEnemigoFinal;
    for (EstadoEnemigo estadoEnemigo: estadosEnemigos) {
        switch (estadoEnemigo.clase) {
            case 1:
                enemigo1Vista->render(estadoEnemigo);
                break;
            case 2:
                enemigo2Vista->render(estadoEnemigo);
				break;

			// El Enemigo Final necesita recibir sus extensiones
			case 3:
				enemigoFinal = estadoEnemigo;
				break;
			case 4:
				extensionesEnemigoFinal.push_back(estadoEnemigo);
				break;
        }
    }

    if (enemigoFinal.clase != -1) {
		enemigoFinal1Vista->render(enemigoFinal, extensionesEnemigoFinal);
    } else {
		explosiones.splice(explosiones.end(), enemigoFinal1Vista->nuevasExplosiones());
		enemigoFinal1Vista->renderMuerte();
    }
}


void ManagerVista::renderDisparos(std::list<EstadoDisparo> estadosDisparos) {
    for (EstadoDisparo estadoDisparo: estadosDisparos) {
    	if ((estadoDisparo.nroJugador & 8)) {
			disparoHelperVista->render(estadoDisparo);
    	} else {
			disparoJugadorVista->render(estadoDisparo);
    	}
    }
}


void ManagerVista::renderDisparosEnemigos(std::list<EstadoDisparo> disparosEnemigos) {
    for (EstadoDisparo estadoDisparo: disparosEnemigos) {
        disparoEnemigoVista->render(estadoDisparo);
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


void ManagerVista::agregarExplosiones(std::list<EstadoEnemigo> enemigos, std::list<EstadoDisparo> disparosJugador,
		std::list<EstadoDisparo> disparosEnemigo, EstadoJugador estadoJugadores[MAX_JUGADORES]) {

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
			case 3:
				// Explosion de enemigo final se agrega en renderEnemigos()
				break;
			case 4:
				explosiones.push_back(enemigoFinal1Vista->nuevaExplosionExt(pos));
				break;
        }
    }

	for (EstadoDisparo d : disparosJugador) {
		if (d.energia > 0) continue;
		Vector pos = Vector(d.posicionX, d.posicionY);
		explosiones.push_back(disparoJugadorVista->nuevaExplosion(pos));
	}

	for (EstadoDisparo d : disparosEnemigo) {
		if (d.energia > 0) continue;
		Vector pos = Vector(d.posicionX, d.posicionY);
		explosiones.push_back(disparoEnemigoVista->nuevaExplosion(pos));
	}

	for (int i = 0; i < MAX_JUGADORES; i++) {
		Vector pos = Vector(estadoJugadores[i].posicionX, estadoJugadores[i].posicionY);
		if (estadoJugadores[i].energia > 0) continue;
		if (estadoJugadores[i].posicionX < 100) continue;
		explosiones.splice(explosiones.end(), (*jugadores)[i]->nuevasExplosiones(pos, estadoJugadores[i].estaMuerto));
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
	hud->render(estadoTick, estadoLogin, username);
}

bool ManagerVista::mutear() {
    return audio->mutear();
}
