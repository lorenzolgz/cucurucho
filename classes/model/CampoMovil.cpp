#include <algorithm>
#include "CampoMovil.h"
#include <string>
#include "../../commons/utils/Log.h"
#include "../../server/classes/model/CampoMovil.h"
#include "../view/Enemigo1Vista.h"
#include "../view/Enemigo2Vista.h"


CampoMovil::CampoMovil(Jugador* jugador, int ancho, int alto, int inicioEnEjeY, float velocidadNivel, float largoNivel) {
	CampoMovil::posicion = Vector(0, 0);
	CampoMovil::velocidadX = velocidadNivel;
	CampoMovil::largoNivel = largoNivel;
    CampoMovil::ancho = ancho;
	CampoMovil::alto = alto;
	CampoMovil::jugador = jugador;
	CampoMovil::vista = new CampoVista(ancho, alto, inicioEnEjeY);
}

void CampoMovil::tick() {
    posicion = Vector(posicion.getX() + velocidadX, posicion.getY());
    vista->render();
    if (jugador) {
        std::for_each(entidadesEnemigos.begin(), entidadesEnemigos.end(), [](Entidad *t) { t->tick(); });
        for (EstadoEnemigo estadoEnemigo : estadosEnemigos) {
			switch (estadoEnemigo.clase) {
				case 1: {
					Enemigo1Vista *enemigo1Vista = new Enemigo1Vista();
					enemigo1Vista->render(Vector(estadoEnemigo.posicionX, estadoEnemigo.posicionY), 0);
					break;
				}
				case 2: {
					Enemigo2Vista *enemigo2Vista = new Enemigo2Vista();
					enemigo2Vista->render(Vector(estadoEnemigo.posicionX, estadoEnemigo.posicionY), 0);
				}
			}
        }
        jugador->tick();
    }
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

float CampoMovil::getVelocidadX() {
	return velocidadX;
}

void CampoMovil::agregarEntidad(Entidad *entidad) {
	entidadesEnemigos.push_back(entidad);
}

bool CampoMovil::entidadEstaDentroDelCampo(Entidad *entidad) {
	return (entidad->getPosicion().getX() + entidad->getAncho() <= ancho) && (entidad->getPosicion().getY() + entidad->getAlto() <= alto) &&
			(entidad->getPosicion().getX() >= 0) && (entidad->getPosicion().getY() >= 0);
}

void CampoMovil::setEstadosEnemigos(std::list<EstadoEnemigo> estadosEnemigos) {
	CampoMovil::estadosEnemigos = estadosEnemigos;
}
