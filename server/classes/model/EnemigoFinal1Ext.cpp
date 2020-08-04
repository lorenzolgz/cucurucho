//
// Created by javier on 19/7/20.
//

#include "EnemigoFinal1Ext.h"
#include "life/VidaEnemigoFinal1.h"
#include "ais/IAEnemigoPatron3Ext.h"
#include "life/VidaEnemigoFinal1Ext.h"
#include "entities/projectiles/DisparoEnemigo1.h"
#include "CampoMovil.h"
#include "entities/projectiles/DisparoEnemigo2.h"

#define TICKS_COOLDOWN_DISPARO 80

#define CANT_MODULOS 10
#define CANT_POSICIONES 90

// 1 para solo la cabeza, CANT_MODULOS para todos
#define MODULOS_COLISIONABLES 1

EnemigoFinal1Ext::EnemigoFinal1Ext(std::map<int, Jugador *> *jugadores, CampoMovil* campo,
		EnemigoFinal1 *padre, Vector posRelativa, Vector inferior, Vector superior) {
	this->posicion = padre->getCentroDeMasa();
	this->ancho = ENEMIGO_FINAL1_EXT_ANCHO;
	this->alto = ENEMIGO_FINAL1_EXT_ALTO;
	this->padre = padre;
	this->vida = new VidaEnemigoFinal1Ext();
	this->campo = campo;
	this->ia = new IAEnemigoPatron3Ext(this, jugadores, padre, posRelativa, inferior, superior);
	this->ticksHastaDisparo = 0;
	for (int i = 0; i < CANT_POSICIONES; i++) {
		this->posiciones.push_back(this->posicion);
	}
	l->info("Se creo correctamente la extension del Enemigo Final 1.");
}

EstadoEnemigo EnemigoFinal1Ext::state() {
	struct EstadoEnemigo estado;
	estado.posicionX = posicion.getX();
	estado.posicionY = posicion.getY();
	estado.energia = vida->getEnergia();
	estado.clase = 4;
	return estado;
}

float EnemigoFinal1Ext::getVelocidadX() {
	return 0;
}

void EnemigoFinal1Ext::setPosicion(Vector nuevaPosicion) {
	this->posicion = nuevaPosicion;
}

void EnemigoFinal1Ext::tick() {
	ticksHastaDisparo > 0 ? ticksHastaDisparo-- : ticksHastaDisparo = 0;
	ia = ia->tick();
	posiciones.push_front(posicion);
	posiciones.pop_back();
}

std::list<Forma> EnemigoFinal1Ext::getFormas() {
	std::list<Forma> formas;

	Vector lock = padre->getPosicion() + Vector(padre->getAncho() / 10, padre->getAlto() / 2);
	for (int i = 0; i < MODULOS_COLISIONABLES; i++) {
		Vector posicion = posiciones[i * CANT_POSICIONES / CANT_MODULOS];
		posicion = posicion - (posicion - lock) / CANT_MODULOS * i;
		formas.push_back(Forma(posicion.getX(), posicion.getY(), this->getAncho(), this->getAlto()));
	}

	return formas;
}

int EnemigoFinal1Ext::getTipoEntidad() {
	return ENTIDAD_ENEMIGO_FINAL1EXT;
}

void EnemigoFinal1Ext::disparar(Vector vector) {
	if (ticksHastaDisparo <= 0) {
		ticksHastaDisparo = TICKS_COOLDOWN_DISPARO;
		DisparoEnemigo2 *disparo = new DisparoEnemigo2(posicion, vector);
		campo->nuevoDisparoEnemigo(disparo);
		l->info("Se crea un nuevo disparo Enemigo 01");
	}
}
