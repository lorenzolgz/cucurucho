#include "Jugador.h"
#include "../../../commons/utils/Utils.h"
#include "../../../commons/utils/Log.h"
#include "CampoMovil.h"

Jugador::Jugador(int x, int y) {
	this->velocidadEscalar = JUGADOR_VELOCIDAD_ESCALAR;
	this->posicion = Vector(x, y);
	this->velocidad = Vector(0, 0);

	this->helperAbove = new Helper(this, Vector(JUGADOR_ANCHO / 2, -JUGADOR_ALTO));
	this->helperBelow = new Helper(this, Vector(JUGADOR_ANCHO / 2, JUGADOR_ALTO * 2));

	this->vidaJugador = new VidaJugador();

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
	struct EstadoJugador estadoJugador;
	estadoJugador.posicionX = posicion.getX();
	estadoJugador.posicionY = posicion.getY();
	estadoJugador.helper1 = helperAbove->state();
	estadoJugador.helper2 = helperBelow->state();
	estadoJugador.puntajeVida = vidaJugador->getPuntajeVida();
	return estadoJugador;
}


const Vector &Jugador::getPosicion() const {
    return posicion;
}

const Vector Jugador::getVelocidad() const {
    return velocidad;
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

void Jugador::resetState() {
    helperAbove->setAngulo(0);
    helperBelow->setAngulo(0);
}
