#include "Enemigo2.h"
#include "../../../commons/utils/Utils.h"
#include "../../../commons/utils/Log.h"
#include "Nivel.h"
#include "../../../commons/utils/Constantes.h"
#include "life/VidaEnemigo2.h"
#include "ais/IAEnemigoPatron2.h"

Enemigo2::Enemigo2(float x,float y, float velocidadX, std::map<int, Jugador*>* jugadores) {
    if (random() % 2 == 0) {
        x = -x + CAMPO_ANCHO - ENEMIGO2_ANCHO;
        velocidadX *= -1;
    }
	this->velocidadEscalar = 1;
	this->posicion = Vector(x, y);
	this->velocidadX = velocidadX;
	this->vida = new VidaEnemigo2();
	this->ia = new IAEnemigoPatron2(this, jugadores);
	l->info("Se creo correctamente el Enemigo 02.");
}

int Enemigo2::getAncho() {
	return ENEMIGO2_ANCHO;
}

int Enemigo2::getAlto() {
	return ENEMIGO2_ALTO;
}

void Enemigo2::tick() {
	ia = ia->tick();
	l->debug("Posicion del Enemigo 02: "+ posicion.getVector());
}

Vector Enemigo2::getPosicion() {
	return posicion;
}

struct EstadoEnemigo Enemigo2::state() {
	struct EstadoEnemigo estado;
	estado.posicionX = posicion.getX();
	estado.posicionY = posicion.getY();
	estado.clase = 2;
	estado.energia = vida->getEnergia();
	return estado;
}

int Enemigo2::getTipoEntidad() {
	return ENTIDAD_ENEMIGO2;
}

std::list<Forma> Enemigo2::getFormas() {
	std::list<Forma> formas;
	Forma formaSimple = Forma(getPosicion().getX(), getPosicion().getY(), getAncho()-20, getAlto());
	formas.emplace_back(formaSimple);
	return formas;
}

VidaEntidad* Enemigo2::getVidaEntidad() {
	return vida;
}

float Enemigo2::getVelocidadX() {
	return velocidadX;
}

void Enemigo2::setPosicion(Vector nuevaPosicion) {
	posicion = nuevaPosicion;
}
