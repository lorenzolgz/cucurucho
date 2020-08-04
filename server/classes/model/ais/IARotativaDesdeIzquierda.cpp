#include "IARotativaDesdeIzquierda.h"
#include "default/IACircular.h"
#include "default/IAHorizontal.h"
#include "default/IAHorizontal2.h"
#include "../../../../commons/utils/Constantes.h"

// !!!!!
IARotativaDesdeIzquierda::IARotativaDesdeIzquierda(EntidadEnemigo *entidadEnemigo, std::map<int, Jugador *> *jugadores) {
	this->entidadEnemigo = entidadEnemigo;
	this->jugadores = jugadores;
	this->primerTick = true;
	this->ticks = 0;

	float posXDondeEmpiezaARotar = 600;
	// float posYDondeEmpiezaARotar = CAMPO_ALTO/2 + entidadEnemigo->getAlto()/2;
	float posYDondeEmpiezaARotar = 400;
	Vector posDondeEmpiezaARotar = Vector(posXDondeEmpiezaARotar, posYDondeEmpiezaARotar);
	l->error("!!!! posDondeEmpiezaARotar " + std::to_string(posDondeEmpiezaARotar.getX()) + " - " + std::to_string(posDondeEmpiezaARotar.getY()));

	// !!!!
	entidadEnemigo->setPosicion(Vector(0, posDondeEmpiezaARotar.getY()));

	IAEnemigo* iaCircular = new IACircular(entidadEnemigo, jugadores, 180, false, Vector(0.45, 1), 120);
	IAEnemigo* iaHorizontal = new IAHorizontal2(entidadEnemigo, jugadores, true, posDondeEmpiezaARotar.getX(), iaCircular);

	this->innerIa = iaHorizontal;
}

IAEnemigo *IARotativaDesdeIzquierda::tick() {
	innerIa = innerIa->tick();
	return this;
}
