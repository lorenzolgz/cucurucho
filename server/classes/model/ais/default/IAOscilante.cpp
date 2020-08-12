//
// Created by javier on 19/7/20.
//

#include "IAOscilante.h"
#include "../../../../../commons/utils/Utils.h"

IAOscilante::IAOscilante(EntidadEnemigo *entidadEnemigo, Vector inferior, Vector superior) {
	this->entidadEnemigo = entidadEnemigo;
	this->inferior = inferior;
	this->superior = superior;
	this->contador = rand() % 360;
}

IAEnemigo *IAOscilante::tick() {
	Vector offset = this->inferior + (this->superior - this->inferior) * pow(sin_d(contador), 2);
	this->entidadEnemigo->setPosicion(offset + this->posInicial);
	this->contador++;
	return this;
}

void IAOscilante::setPosInicial(const Vector &posInicial) {
	IAOscilante::posInicial = posInicial;
}
