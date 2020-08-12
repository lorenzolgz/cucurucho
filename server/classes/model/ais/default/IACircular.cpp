#include <cmath>
#include "IACircular.h"
#include "../../../../../commons/utils/Utils.h"

IACircular::IACircular(EntidadEnemigo *entidadEnemigo, std::map<int, Jugador *> *jugadores, int anguloInicialGrados, bool sentidoHorario, Vector factor, float radio, int totalAnguloGrados, IAEnemigo* next) {
	this->entidadEnemigo = entidadEnemigo;
	this->jugadores = jugadores;
	this->next = next;
	this->primerTick = true;
	this->ticks = 0;
	this->anguloInicialGrados = anguloInicialGrados;
	this->sentidoHorario = sentidoHorario;
	this->factorModificadorPosicion = factor;
	this->radio = radio;
	this->totalAnguloGrados = totalAnguloGrados;
}

IAEnemigo *IACircular::tick() {
	if (primerTick) {
		Vector posicionInicial = this->entidadEnemigo->getPosicion();
		Vector deltaPosInicial = calcularDeltaPosicion(anguloInicialGrados);
		this->centro = posicionInicial - deltaPosInicial;
		primerTick = false;
	}
	if (ticks == totalAnguloGrados) {
		return next;
	}

	ticks = ticks + 1;

	int factorModificadorRotacion = sentidoHorario ? 1 : -1;
	int anguloGrados = anguloInicialGrados + (ticks * factorModificadorRotacion);
	Vector deltaPos = calcularDeltaPosicion(anguloGrados);
	entidadEnemigo->setPosicion(centro + deltaPos);

	return this;
}

Vector IACircular::calcularDeltaPosicion(int anguloGrados) {
	float deltaPosX = radio * cos_d(anguloGrados) * factorModificadorPosicion.getX();
	float deltaPosY = radio * sin_d(anguloGrados) * factorModificadorPosicion.getY();

	return Vector(deltaPosX, deltaPosY);
}

void IACircular::setNext(IAEnemigo *nuevoNext) {
	this->next = nuevoNext;
}

void IACircular::inicializar() {
	IAEnemigo::inicializar();
	ticks = 0;
}
