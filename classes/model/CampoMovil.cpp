#include <cstdlib>
#include <algorithm>
#include "CampoMovil.h"
#include "../Log.h"

CampoMovil::CampoMovil(Jugador* jugador, int ancho, int alto, int inicioEnEjeY) {
	CampoMovil::posicion = Vector(0, 0);
	CampoMovil::velocidadX = 3;
	CampoMovil::ancho = ancho;
	CampoMovil::alto = alto;
	CampoMovil::jugador = jugador;
	CampoMovil::vista = new CampoVista(ancho, alto, inicioEnEjeY);
}

void CampoMovil::tick() {
	posicion = Vector(posicion.getX() + velocidadX, posicion.getY());
	vista->render();
	std::for_each(entidades.begin(), entidades.end(), [](Entidad* t) { t->tick(); });
	jugador->tick();
}

FondoVista * CampoMovil::nuevoFondo(const std::string &fileName, float xOffset, int yFondo, float modVelocidad) {
	return vista->nuevoFondo(fileName, xOffset, yFondo, modVelocidad, &velocidadX);
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

int CampoMovil::getVelocidadX() {
	return velocidadX;
}

void CampoMovil::agregarEntidad(Entidad *entidad) {
	entidades.push_back(entidad);
}

bool CampoMovil::entidadEstaDentroDelCampo(Entidad *entidad) {
	return (entidad->getPosicion().getX() + entidad->getAncho() < ancho) && (entidad->getPosicion().getY() + entidad->getAlto() < alto);
}
