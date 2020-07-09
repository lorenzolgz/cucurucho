#include <algorithm>
#include "CampoMovil.h"
#include <string>
#include "../../../commons/utils/Log.h"

CampoMovil::CampoMovil(std::map<int, Jugador *> jugadores, int ancho, int alto, int inicioEnEjeY, float velocidadNivel, float largoNivel) {
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
    for (auto* entidadEnemigo : entidadesEnemigos) {
    	entidadEnemigo->tick();
    }
    std::map<int, Jugador*>::iterator it;
    for (it = jugadores.begin(); it != jugadores.end(); it++) {
        it->second->tick();
    }

    std::list<EntidadEnemigo*>* entidadesEnemigasColisionadas = new std::list<EntidadEnemigo*>();
	for (it = jugadores.begin(); it != jugadores.end(); it++) {
		Jugador* jugador = it->second;
		for (auto* entidadEnemigo : entidadesEnemigos) {
			if (colisionan(jugador, entidadEnemigo)) {
				l->error("!!!! colisionan");
				entidadesEnemigasColisionadas->emplace_back(entidadEnemigo);
			}
		}
	}

	for (auto* entidadEnemigo : *entidadesEnemigasColisionadas) {
		removerEntidadEnemigo(entidadEnemigo);
	}
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
	for (EntidadEnemigo* entidadEnemigo : entidadesEnemigos) {
        if (verificarPosicionEnemigo(entidadEnemigo)) estadosEnemigos.push_back(entidadEnemigo->state());
	}

    std::map<int, Jugador*>::iterator it;
    for (it = jugadores.begin(); it != jugadores.end(); it++) {
        estadosJugadores.push_back(it->second->state());
    }

	// EstadoInternoCampoMovil* estadoCampoMovil ;= new EstadoInternoCampoMovil(jugador->state(), estadosEnemigos)
	EstadoInternoCampoMovil estadoCampoMovil;
	estadoCampoMovil.estadosJugadores = estadosJugadores;
	estadoCampoMovil.estadosEnemigos = estadosEnemigos;
	estadoCampoMovil.posX = (int) posicion.getX();

	return estadoCampoMovil;
}

bool CampoMovil::verificarPosicionEnemigo(EntidadEnemigo *pEnemigo) {
    int posX = pEnemigo->getPosicion().getX();
    int posY = pEnemigo->getPosicion().getY();
    return !(posX < 0 - CAMPO_OFFSET || posX > ancho + CAMPO_OFFSET || posY < 0 - CAMPO_OFFSET || posY > alto + CAMPO_OFFSET);
}

bool CampoMovil::colisionan(Entidad* e1, Entidad* e2) {
	return e1->getPosicion().getX() < e2->getPosicion().getX() + e2->getAncho() &&
		e1->getPosicion().getX() + e1->getAncho() > e2->getPosicion().getX() &&
		e1->getPosicion().getY() < e2->getPosicion().getY() + e2->getAlto() &&
		e1->getPosicion().getY() + e1->getAlto() > e2->getPosicion().getY();
}

void CampoMovil::removerEntidadEnemigo(EntidadEnemigo* entidadEnemigo) {
	auto it = entidadesEnemigos.begin();
	while (it != entidadesEnemigos.end()) {
		EntidadEnemigo* e = *it;
		if (e == entidadEnemigo) {
			it = entidadesEnemigos.erase(it);
			break;
		}
		++it;
	}
}

