#include "Enemigo1.h"
#include "../../../commons/utils/Utils.h"
#include "../../../commons/utils/Log.h"
#include "Nivel.h"
#include "../../../commons/utils/Constantes.h"
#include "life/VidaEnemigo1.h"
#include "ais/IAEnemigoPatron1.h"
#include "entities/projectiles/DisparoEnemigo1.h"


Enemigo1::Enemigo1(float x, float y, float velocidadX, std::map<int, Jugador*>* jugadores, CampoMovil* campo) {
		if (random() % 10 < 2) {
        x = -x + CAMPO_ANCHO - ENEMIGO1_ANCHO;
        velocidadX *= -1;
    }
	this->posicion = Vector(x, y);
	this->ultimaPosicion = this->posicion;
	this->ultimoAngulo = 0;
	this->ancho = ENEMIGO1_ANCHO;
	this->alto = ENEMIGO1_ALTO;
	this->velocidadX = velocidadX; // Posición 2 de sprite
    this->ticksHastaDisparo = 0;
    this->campo = campo;
	this->vida = new VidaEnemigo1();
	this->ia = new IAEnemigoPatron1(this, jugadores);
	l->info("Se creo correctamente el Enemigo 01.");
}

void Enemigo1::tick() {
	ia = ia->tick();
    ticksHastaDisparo > 0 ? ticksHastaDisparo-- : ticksHastaDisparo = 0;

    l->debug("Posicion del Enemigo 01: "+ posicion.getVector());
}

struct EstadoEnemigo Enemigo1::state() {
	struct EstadoEnemigo estado;
	Vector velocidad = posicion - ultimaPosicion;

	if (velocidad.modulo() > 2) {
		ultimoAngulo = velocidad.arg();
		ultimaPosicion = posicion;
	}

	estado.posicionX = posicion.getX();
	estado.posicionY = posicion.getY();
    estado.clase = 1;
    estado.energia = vida->getEnergia();
    estado.anguloDir = ultimoAngulo;
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

void Enemigo1::disparar(Vector direccion) {

    if (ticksHastaDisparo <= 0) {
        ticksHastaDisparo = TICKS_COOLDOWN_DISPARO_ENEMIGO1;
        DisparoEnemigo1 *disparo = new DisparoEnemigo1(posicion, direccion);
        campo->nuevoDisparoEnemigo(disparo);
        l->info("Se crea un nuevo disparo Enemigo 01");
    }

}