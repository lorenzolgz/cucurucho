#include "IAEnemigoPatron3.h"
#include "default/IACircular.h"
#include "default/IAEstatico.h"
#include "default/IAHorizontal.h"
#include "default/IACircularHC.h"

IAEnemigoPatron3::IAEnemigoPatron3(EntidadEnemigo *entidadEnemigo, std::map<int, Jugador *> *jugadores) {
	this->entidadEnemigo = entidadEnemigo;
	this->jugadores = jugadores;

	this->iaCircular = new IACircularHC(entidadEnemigo, jugadores, Vector(0.45, 1), 80);
	this->iaEstatico = new IAEstatico(entidadEnemigo, jugadores, 5, iaCircular);
	this->iaHorizontal = new IAHorizontal(entidadEnemigo, jugadores, 25, iaEstatico);

	this->innerIa = iaHorizontal;
}

IAEnemigo *IAEnemigoPatron3::tick() {
	innerIa = innerIa->tick();
	return this;
}

IAEnemigoPatron3::~IAEnemigoPatron3() {
	delete this->iaCircular;
	delete this->iaEstatico;
	delete this->iaHorizontal;
}
