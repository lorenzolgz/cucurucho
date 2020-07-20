#include "IAEnemigoPatron3.h"
#include "default/IACircular.h"
#include "default/IAEstatico.h"
#include "default/IAHorizontal.h"

IAEnemigoPatron3::IAEnemigoPatron3(EntidadEnemigo *entidadEnemigo, std::map<int, Jugador *> *jugadores) {
	this->entidadEnemigo = entidadEnemigo;
	this->jugadores = jugadores;

	IAEnemigo* iaCircular = new IACircular(entidadEnemigo, jugadores, Vector(0.45, 1), 80);
	IAEnemigo* iaEstatico = new IAEstatico(entidadEnemigo, jugadores, 5, iaCircular);
	IAEnemigo* iaHorizontal = new IAHorizontal(entidadEnemigo, jugadores, 25, iaEstatico);

	this->innerIa = iaHorizontal;
}

IAEnemigo *IAEnemigoPatron3::tick() {
	innerIa = innerIa->tick();
}
