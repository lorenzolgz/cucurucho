#include "Jugador.h"
#include "../../../commons/utils/Utils.h"
#include "../../../commons/utils/Log.h"
#include "CampoMovil.h"
#include "life/VidaJugadorInvencible.h"

Jugador::Jugador(Configuracion* config, int nroJugador) {
	this->config = config;
	this->nroJugador = nroJugador;
	this->velocidadEscalar = JUGADOR_VELOCIDAD_ESCALAR;
	this->ancho = JUGADOR_ANCHO;
	this->alto = JUGADOR_ALTO;
	this->velocidad = Vector(0, 0);
	this->ticksHastaDisparo = 0;

	this->helperAbove = new Helper(this, Vector(JUGADOR_ANCHO / 2, -JUGADOR_ALTO));
	this->helperBelow = new Helper(this, Vector(JUGADOR_ANCHO / 2, JUGADOR_ALTO * 2));

	this->vida = new VidaJugador();
	this->posicion = calcularPosicionInicial();
	this->puntos = 0;
	this->puntosParcial.push_back(0);
	this->agregarPuntajeParcial = false;
	this->acumulado = 0;

    l->info("Se creo correctamente el Jugador.");
}

void Jugador::calcularVectorVelocidad(bool arriba, bool abajo, bool izquierda, bool derecha) {
	if (vida->estaEnCooldownInmovilPostNacer()) {
		velocidad = Vector(0, 0);
		return;
	}

    double velocidadParcial = 0;

    if ((arriba || abajo) && (izquierda || derecha)) {
		velocidadParcial = velocidadEscalar / sqrt(2);
    } else if (arriba || abajo || izquierda || derecha) {
		velocidadParcial = velocidadEscalar;
    }

    double velocidadX = 0, velocidadY = 0;
    if (arriba) {
		velocidadY = -velocidadParcial;
    } else if (abajo) {
		velocidadY = velocidadParcial;
    }

    if (izquierda) {
		velocidadX = -velocidadParcial;
    } else if (derecha) {
		velocidadX = velocidadParcial;
    }

    velocidad = Vector(velocidadX, velocidadY);
}

Vector Jugador::actualizarPosicion(Vector posicionNueva) {
	Vector posicionAnterior = posicion;
	posicion = posicionNueva;

	if (!campo->entidadEstaDentroDelCampo(this)) {
		posicion = posicionAnterior;
	}
	return posicion;
}

bool Jugador::puedeDisparar() {
	return ticksHastaDisparo <= 0;
}

Disparo* Jugador::disparar() {
	if (estaMuerto()) {
		return nullptr;
	}
	if (!this->puedeDisparar()) {
		return nullptr;
	}

	ticksHastaDisparo = TICKS_COOLDOWN_DISPARO;
	return new Disparo(getPosicion().getX(), getPosicion().getY(), this);
}

void Jugador::tick() {
	actualizarPosicion(posicion + Vector(velocidad.getX(), 0));
	actualizarPosicion(posicion + Vector(0, velocidad.getY()));
	helperAbove->tick();
	helperBelow->tick();

	ticksHastaDisparo > 0 ? ticksHastaDisparo-- : ticksHastaDisparo = 0;

	if (vida->isAcabaDePerderUnaVida()) {
		l->info("El jugador " + std::to_string(nroJugador) + " perdio una vida.");
		reiniciarPosicion();
	}
	vida->tick();

	if (agregarPuntajeParcial) {
		this->puntosParcial.push_back(this->acumulado);
		agregarPuntajeParcial = false;
	}
    l->debug("Posicion del Jugador: "+ posicion.getVector());
}

struct EstadoJugador Jugador::state() {
	struct EstadoJugador estadoJugador;
	estadoJugador.posicionX = posicion.getX();
	estadoJugador.posicionY = posicion.getY();
	estadoJugador.helper1 = helperAbove->state();
	estadoJugador.helper2 = helperBelow->state();
	estadoJugador.energia = !vida->isAcabaDePerderUnaVida() * vida->getEnergia();
	estadoJugador.cantidadVidas = vida->getCantidadVidas();
	estadoJugador.esInvencible = vida->esInvencible();
	estadoJugador.estaMuerto = estaMuerto();
	estadoJugador.puntos = this->puntos;
	estadoJugador.puntosParciales = this->puntosParcial;
	return estadoJugador;
}

const Vector Jugador::getVelocidad() const {
    return velocidad;
}

void Jugador::setCampo(CampoMovil *campo) {
	this->campo = campo;
}

void Jugador::reiniciarPosicion() {
    helperAbove->setAngulo(0);
    helperBelow->setAngulo(0);
    posicion = calcularPosicionInicial();
	vida->nacer();
}

int Jugador::getTipoEntidad() {
	return ENTIDAD_JUGADOR;
}

VidaEntidad* Jugador::getVidaEntidad() {
	return vida;
}

void Jugador::cambiarInvencible(bool invencible) {
	vida->cambiarInvencible(invencible);
}

Vector Jugador::calcularPosicionInicial() {
	if (this->estaMuerto()) {
		return Vector(-10000, -10000);
	}
	return Vector(config->getAnchoPantalla() / 8 * (nroJugador + 1), config->getAltoPantalla() / 2);
}

bool Jugador::estaMuerto() {
	return vida->estaMuerto();
}

void Jugador::sumarPuntosPorDestruirA(int entidadEnemigo){
    switch(entidadEnemigo){
        case ENTIDAD_ENEMIGO1: {
            this->puntos += 500;
            this->acumulado += 500;
            break;
        }
        case ENTIDAD_ENEMIGO2: {
            this->puntos += 1000;
            this->acumulado += 1000;
            break;
        }
        case ENTIDAD_ENEMIGO_FINAL1: {
            this->puntos += 2000;
            this->acumulado += 2000;
            break;
        }
        case ENTIDAD_ENEMIGO_FINAL1EXT: {
			this->puntos += 0;
			this->acumulado += 0;
			break;
        }
        default: {
            this->puntos = -1;
            this->acumulado = -1;
        }
    }
	this->puntosParcial.pop_back();
	this->puntosParcial.push_back(this->acumulado);
}

void Jugador::finNivel(){
	this->agregarPuntajeParcial = true;
    this->acumulado = 0;
}

int Jugador::getNroJugador() {
	return nroJugador;
}
