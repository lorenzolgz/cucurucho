#include "Jugador.h"
#include "../../../commons/utils/Utils.h"
#include "../../../commons/utils/Log.h"
#include "CampoMovil.h"


Jugador::Jugador(int x, int y) {
	Jugador::velocidadEscalar = JUGADOR_VELOCIDAD_ESCALAR;
	Jugador::posicion = Vector(x, y);
	Jugador::velocidad = Vector(0, 0);

	Jugador::helperAbove = new Helper(this, Vector(JUGADOR_ANCHO / 2, -JUGADOR_ALTO));
	Jugador::helperBelow = new Helper(this, Vector(JUGADOR_ANCHO / 2, JUGADOR_ALTO * 2));
    l->info("Se creo correctamente el Jugador.");
}

void Jugador::calcularVectorVelocidad(bool arriba, bool abajo, bool izquierda, bool derecha) {
    double vParcial = 0;

    if ((arriba || abajo) && (izquierda || derecha)) {
        vParcial = velocidadEscalar / sqrt(2);
    } else if (arriba || abajo || izquierda || derecha) {
        vParcial = velocidadEscalar;
    }

    double vx = 0, vy = 0;
    if (arriba) {
        vy = -vParcial;
    } else if (abajo) {
        vy = vParcial;
    }

    if (izquierda) {
        vx = -vParcial;
    } else if (derecha) {
        vx = vParcial;
    }

    velocidad = Vector(vx, vy);
}

Vector Jugador::actualizarPosicion(Vector posicionNueva) {
	Vector posicionAnterior = posicion;
	posicion = posicionNueva;

	if (!campo->entidadEstaDentroDelCampo(this)) {
		posicion = posicionAnterior;
	}
	return posicion;
}

void Jugador::tick() {
	actualizarPosicion(posicion + Vector(velocidad.getX(), 0));
	actualizarPosicion(posicion + Vector(0, velocidad.getY()));
	helperAbove->tick();
	helperBelow->tick();
    l->debug("Posicion del Jugador: "+ posicion.getVector());
}

struct EstadoJugador Jugador::state() {
	struct EstadoJugador view;
	view.posicionX = posicion.getX();
	view.posicionY = posicion.getY();
	view.helper1 = helperAbove->state();
	view.helper2 = helperBelow->state();
	return view;
}


const Vector &Jugador::getPosicion() const {
    return posicion;
}

const Vector Jugador::getVelocidad() const {
    return velocidad;
}

int Jugador::getContador() const {
}

void Jugador::setPosicion(int x, int y) {
    Jugador::posicion = Vector(x, y);
}

void Jugador::setCampo(CampoMovil *campo) {
	this->campo = campo;
}

int Jugador::getAncho() {
	return JUGADOR_ANCHO;
}

int Jugador::getAlto() {
	return JUGADOR_ALTO;
}

Vector Jugador::getPosicion() {
	return posicion;
}
