#include <algorithm>
#include "CampoMovil.h"
#include <string>
#include "../../../commons/utils/Log.h"

CampoMovil::CampoMovil(std::map<int, Jugador *> jugadores, int ancho, int alto, float velocidadNivel, float largoNivel) {
	CampoMovil::posicion = Vector(0, 0);
	CampoMovil::velocidadX = velocidadNivel;
	CampoMovil::largoNivel = largoNivel;
    CampoMovil::ancho = ancho;
	CampoMovil::alto = alto;
	CampoMovil::jugadores = jugadores;

    std::map<int, Jugador*>::iterator it;
    for (it = jugadores.begin(); it != jugadores.end(); it++) {
        it->second->setCampo(this);
    }
}

void CampoMovil::tick() {
	posicion = Vector(posicion.getX() + velocidadX, posicion.getY());
	for (auto *entidadEnemigo : entidadesEnemigos) {
		if(entidadEnemigo->getTipoEntidad() == ENTIDAD_ENEMIGO1){
            entidadEnemigo->aproximarAJugador(jugadores);
		} else {
            entidadEnemigo->tick();
        }
	}
	std::map<int, Jugador *>::iterator it;
	for (it = jugadores.begin(); it != jugadores.end(); it++) {
		it->second->tick();
	}

	procesarTodasLasColisiones();
	removerEntidadesEnemigosMuertas();
	removerDisparosMuertos();
	removerDisparosFueraDePantalla();
}

int CampoMovil::getAncho() {
	return ancho;
}

int CampoMovil::getAlto() {
	return alto;
}

Vector CampoMovil::getPosicion() {
	return posicion;
}

float CampoMovil::getVelocidadX() {
	return velocidadX;
}

void CampoMovil::agregarEntidadEnemigo(EntidadEnemigo *entidad) {
	entidadesEnemigos.push_back(entidad);
}

bool CampoMovil::entidadEstaDentroDelCampo(Entidad *entidad) {
	return (entidad->getPosicion().getX() + entidad->getAncho() <= ancho) && (entidad->getPosicion().getY() + entidad->getAlto() <= alto) &&
			(entidad->getPosicion().getX() >= 0) && (entidad->getPosicion().getY() >= 0);
}

bool CampoMovil::verificarPosicionNivel() {
    return posicion.getX() > (largoNivel + ancho);
}

EstadoInternoCampoMovil CampoMovil::state() {
	std::list<EstadoEnemigo> estadosEnemigos;
    std::list<EstadoJugador> estadosJugadores;
	std::list<EstadoDisparo> estadosDisparos;
	for (EntidadEnemigo* entidadEnemigo : entidadesEnemigos) {
		// En vez de eliminar a los enemigos que estan fuera del campo, simplemente no los enviamos a los clientes.
        if (verificarEntidadEstaDentroDelCampo(entidadEnemigo)) estadosEnemigos.push_back(entidadEnemigo->state());
	}

    std::map<int, Jugador*>::iterator it;
    for (it = jugadores.begin(); it != jugadores.end(); it++) {
        estadosJugadores.push_back(it->second->state());
    }

	for (Disparo* disparo : disparos) {
		estadosDisparos.push_back(disparo->state());
	}

	// EstadoInternoCampoMovil* estadoCampoMovil ;= new EstadoInternoCampoMovil(jugador->state(), estadosEnemigos)
	EstadoInternoCampoMovil estadoCampoMovil;
	estadoCampoMovil.estadosJugadores = estadosJugadores;
	estadoCampoMovil.estadosEnemigos = estadosEnemigos;
	estadoCampoMovil.estadosDisparos = estadosDisparos;
	estadoCampoMovil.posX = (int) posicion.getX();

	return estadoCampoMovil;
}

bool CampoMovil::verificarEntidadEstaDentroDelCampo(Entidad* entidad) {
    int posX = entidad->getPosicion().getX();
    int posY = entidad->getPosicion().getY();
    return !(posX < 0 - CAMPO_OFFSET || posX > ancho + CAMPO_OFFSET || posY < 0 - CAMPO_OFFSET || posY > alto + CAMPO_OFFSET);
}

void CampoMovil::removerEntidadesEnemigosMuertas() {
	auto it = entidadesEnemigos.begin();
	while (it != entidadesEnemigos.end()) {
		EntidadEnemigo* entidadEnemigo = *it;
		if (entidadEnemigo->getVidaEntidad()->estaMuerto()) {
			it = entidadesEnemigos.erase(it);
		} else {
			++it;
		}
	}
}

void CampoMovil::removerDisparosMuertos() {
	auto it = disparos.begin();
	while (it != disparos.end()) {
		Disparo* disparo = *it;
		if (disparo->getVidaEntidad()->estaMuerto()) {
			it = disparos.erase(it);
		} else {
			++it;
		}
	}
}

void CampoMovil::procesarTodasLasColisiones() {
	for (auto it = jugadores.begin(); it != jugadores.end(); it++) {
		Jugador* jugador = it->second;
		if (jugador->estaMuerto()) {
			continue;
		}
		for (auto* entidadEnemigo : entidadesEnemigos) {
			procesarColisionEntreDosEntidades(jugador, entidadEnemigo);
		}
	}

	for (auto it = disparos.begin(); it != disparos.end(); it++) {
		Disparo* disparo = *it;
		for (auto* entidadEnemigo : entidadesEnemigos) {
			procesarColisionEntreDosEntidades(disparo, entidadEnemigo);
		}
	}
}

void CampoMovil::procesarColisionEntreDosEntidades(Entidad* e1, Entidad* e2) {
	if (e1->colisiona(e2)) {
		e1->getVidaEntidad()->procesarColision(e2->getTipoEntidad());
		e2->getVidaEntidad()->procesarColision(e1->getTipoEntidad());
	}
}

void CampoMovil::nuevoDisparo(Disparo *pDisparo) {
	disparos.push_back(pDisparo);
}

void CampoMovil::removerDisparosFueraDePantalla() {
	std::list<Disparo *>::iterator itd = disparos.begin();

	while (itd != disparos.end()) {
		(*itd)->tick();
		if (!entidadEstaDentroDelCampo(*itd)) {
			itd = disparos.erase(itd);
			l->debug("Disparo eliminado por salir de pantalla.");
		} else {
			itd++;
		}
	}
}
