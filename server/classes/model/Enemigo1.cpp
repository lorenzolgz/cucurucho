#include "Enemigo1.h"
#include "../../../commons/utils/Utils.h"
#include "../../../commons/utils/Log.h"
#include "Nivel.h"
#include "../../../commons/utils/Constantes.h"
#include "life/VidaEnemigo1.h"
#include "ais/IAEnemigoPatron1.h"


Enemigo1::Enemigo1(float x, float y, float velocidadX, std::map<int, Jugador*>* jugadores) {
    if (random() % 10 < 2) {
        x = -x + CAMPO_ANCHO - ENEMIGO1_ANCHO;
        velocidadX *= -1;
    }
	this->posicion = Vector(x, y);
	this->ancho = ENEMIGO1_ANCHO;
	this->alto = ENEMIGO1_ALTO;
	this->velocidadX = velocidadX; // Posición 2 de sprite
	this->vida = new VidaEnemigo1();
	this->ia = new IAEnemigoPatron1(this, jugadores);
	l->info("Se creo correctamente el Enemigo 01.");
}

void Enemigo1::tick() {
	ia = ia->tick();
	l->debug("Posicion del Enemigo 01: "+ posicion.getVector());
}

struct EstadoEnemigo Enemigo1::state() {
	struct EstadoEnemigo estado;
	estado.posicionX = posicion.getX();
	estado.posicionY = posicion.getY();
    estado.clase = 1;
    estado.energia = vida->getEnergia();
	return estado;
}

int Enemigo1::getTipoEntidad() {
	return ENTIDAD_ENEMIGO1;
}

float Enemigo1::getVelocidadX() {
	return velocidadX;
}

void Enemigo1::setPosicion(Vector nuevaPosicion) {
	posicion = nuevaPosicion;
}
