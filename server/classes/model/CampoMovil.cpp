#include <algorithm>
#include "CampoMovil.h"
#include <string>
#include "../../../commons/utils/Log.h"

CampoMovil::CampoMovil(Jugador* jugador, int ancho, int alto, int inicioEnEjeY, float velocidadNivel, float largoNivel) {
	CampoMovil::posicion = Vector(0, 0);
	CampoMovil::velocidadX = velocidadNivel;
	CampoMovil::largoNivel = largoNivel;
    CampoMovil::ancho = ancho;
	CampoMovil::alto = alto;
	CampoMovil::jugador = jugador;

	jugador->setCampo(this);
}

void CampoMovil::tick() {
    posicion = Vector(posicion.getX() + velocidadX, posicion.getY());
    if (jugador) {
        std::for_each(entidadesEnemigos.begin(), entidadesEnemigos.end(), [](EntidadEnemigo *t) { t->tick(); });
        jugador->tick();
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

bool CampoMovil::verificarPosicion() {
    return posicion.getX() > (largoNivel + ancho);
}

EstadoInternoCampoMovil CampoMovil::state() {
	std::list<EstadoEnemigo> estadosEnemigos;

	for (EntidadEnemigo* entidadEnemigo : entidadesEnemigos) {
		estadosEnemigos.push_back(entidadEnemigo->state());
	}

	// EstadoInternoCampoMovil* estadoCampoMovil ;= new EstadoInternoCampoMovil(jugador->state(), estadosEnemigos)
	EstadoInternoCampoMovil estadoCampoMovil;
	estadoCampoMovil.estadoJugador = jugador->state();
	estadoCampoMovil.estadosEnemigos = estadosEnemigos;

	return estadoCampoMovil;
}

