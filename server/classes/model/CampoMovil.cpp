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

    procesarColisiones();
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

// !!!!! pasar a formas
bool colisionanFormas(Forma f1, Forma f2) {
	return f1.getPosX() < f2.getPosX() + f2.getAncho() &&
		   f1.getPosX() + f1.getAncho() > f2.getPosX() &&
		   f1.getPosY() < f2.getPosY() + f2.getAlto() &&
		   f1.getPosY() + f1.getAlto() > f2.getPosY();
}

// !!!!! pasar a entidades
bool CampoMovil::colisionanEntidades(Entidad* e1, Entidad* e2) {
	std::list<Forma> formas1 = e1->getFormas();
	std::list<Forma> formas2 = e2->getFormas();
	// !!!!!
	// std::list<Forma>::iterator it1;
	// std::list<Forma>::iterator it2;

	for (auto it1 = formas1.begin(); it1 != formas1.end(); it1++) {
		for (auto it2 = formas2.begin(); it2 != formas2.end(); it2++) {
			if (colisionanFormas(*it1, *it2)) {
				return true;
			}
		}
	}

	return false;
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

void CampoMovil::procesarColisiones() {
	std::list<EntidadEnemigo*>* entidadesEnemigasColisionadas = new std::list<EntidadEnemigo*>();

	std::map<int, Jugador*>::iterator it;
	for (it = jugadores.begin(); it != jugadores.end(); it++) {
		Jugador* jugador = it->second;
		for (auto* entidadEnemigo : entidadesEnemigos) {
			if (colisionanEntidades(jugador, entidadEnemigo)) {
				entidadesEnemigasColisionadas->emplace_back(entidadEnemigo);
				jugador->getVidaEntidad()->procesarColision(entidadEnemigo->getTipoEntidad());
			}
		}
	}

	for (auto* entidadEnemigo : *entidadesEnemigasColisionadas) {
		removerEntidadEnemigo(entidadEnemigo);
	}
}

