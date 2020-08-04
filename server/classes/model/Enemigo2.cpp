#include "Enemigo2.h"
#include "../../../commons/utils/Utils.h"
#include "../../../commons/utils/Log.h"
#include "Nivel.h"
#include "../../../commons/utils/Constantes.h"
#include "life/VidaEnemigo2.h"
#include "ais/IAEnemigoPatron2.h"
#include "entities/projectiles/DisparoEnemigo2.h"
#include "ais/IARotativaDesdeIzquierda.h"


Enemigo2::Enemigo2(float x,float y, float velocidadX, std::map<int, Jugador*>* jugadores, CampoMovil* campo) {
	if (random() % 10 < 2) {
        x = -x + CAMPO_ANCHO - ENEMIGO2_ANCHO;
        velocidadX *= -1;
    }
	this->posicion = Vector(x, y);
	this->ancho = ENEMIGO2_ANCHO;
	this->alto = ENEMIGO2_ALTO;
	this->velocidadX = velocidadX;
	this->vida = new VidaEnemigo2();
	this->ia = new IARotativaDesdeIzquierda(this, jugadores);
	this->campo = campo;
	l->info("Se creo correctamente el Enemigo 02.");
}

void Enemigo2::tick() {
	ia = ia->tick();

    ticksHastaDisparo > 0 ? ticksHastaDisparo-- : ticksHastaDisparo = 0;
    l->debug("Posicion del Enemigo 02: "+ posicion.getVector());
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

float Enemigo2::getVelocidadX() {
	return velocidadX;
}

void Enemigo2::setPosicion(Vector nuevaPosicion) {
	posicion = nuevaPosicion;
}

void Enemigo2::disparar(Vector direccion) {
    if (ticksHastaDisparo <= 0) {
        ticksHastaDisparo = TICKS_COOLDOWN_DISPARO_ENEMIGO2;
        DisparoEnemigo2 *disparo = new DisparoEnemigo2(posicion, direccion);
        campo->nuevoDisparoEnemigo(disparo);
        l->info("Se crea un nuevo disparo Enemigo 02");
    }

}
