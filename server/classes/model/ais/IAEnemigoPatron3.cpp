#include "IAEnemigoPatron3.h"
#include "default/IACircular.h"
#include "default/IAEstatico.h"
#include "default/IAHorizontal.h"

IAEnemigoPatron3::IAEnemigoPatron3(EntidadEnemigo *entidadEnemigo, std::map<int, Jugador *> *jugadores) {
	this->entidadEnemigo = entidadEnemigo;
	this->jugadores = jugadores;

	IAEnemigo* iaCircular = new IACircular(entidadEnemigo, jugadores, Vector(0.5, 1), 120);
	IAEnemigo* iaEstatico = new IAEstatico(entidadEnemigo, jugadores, 10, iaCircular);
	IAEnemigo* iaHorizontal = new IAHorizontal(entidadEnemigo, jugadores, 100, iaEstatico);

	this->innerIa = iaHorizontal;
}

IAEnemigo *IAEnemigoPatron3::tick() {
	innerIa = innerIa->tick();
}
