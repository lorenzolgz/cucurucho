//
// Created by javier on 19/7/20.
//

#include <map>
#include "IAEnemigoPatron3Ext.h"
#include "../EntidadEnemigo.h"
#include "../../../../commons/utils/Utils.h"
#include "../EnemigoFinal1.h"
#include "default/IAOscilante.h"

const int AMPLITUD_Y = 125;
const int OFFSET_X = -150 - ENEMIGO_FINAL1_ANCHO / 2;

IAEnemigoPatron3Ext::IAEnemigoPatron3Ext(EntidadEnemigo *entidadEnemigo, std::map<int, Jugador *> *jugadores,
										 EntidadEnemigo *padre,
										 Vector posRelativa, Vector inferior, Vector superior) {
	this->entidad = entidadEnemigo;
	this->jugadores = jugadores;
	this->padre = padre;
	this->posRelativa = posRelativa;
	this->contador = rand() % 360;
	this->iaMovimiento = new IAOscilante(entidadEnemigo, inferior, superior);
}

IAEnemigo *IAEnemigoPatron3Ext::tick() {
	this->iaMovimiento->setPosInicial(padre->getCentroDeMasa() + posRelativa);
	this->iaMovimiento->tick();
	this->jugadores->size();

	auto it = this->jugadores->begin();
	std::advance(it, rand() % this->jugadores->size());
	if (rand() % 10 == 0 && !it->second->estaMuerto()) {
		this->entidad->disparar(this->entidad->getCentroDeMasa() - it->second->getCentroDeMasa());
	}
	return this;
}
