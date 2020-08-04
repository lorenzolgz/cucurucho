#include "math.h"
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

	float minimoMargenY = 20 + random() % 30;
	float factodModificadorRadioY = 0.40 + random() % 15 / 100; // !!!! random
	float margenDerecho = 50 + random() % 200; // !!!! random
	float radio = 120 + random() % 20; // !!!! random
	float posXDondeEmpiezaARotar = CAMPO_ANCHO - margenDerecho - entidadEnemigo->getAncho();
	float posYDondeEmpiezaARotar = (minimoMargenY + radio * factodModificadorRadioY) +
			random() % (long) (floor(1.0 * CAMPO_ALTO - entidadEnemigo->getAlto() - 2 * radio * factodModificadorRadioY - minimoMargenY)); // !!!! random
	Vector posDondeEmpiezaARotar = Vector(posXDondeEmpiezaARotar, posYDondeEmpiezaARotar);
	l->error("!!!! posDondeEmpiezaARotar " + std::to_string(posDondeEmpiezaARotar.getX()) + " - " + std::to_string(posDondeEmpiezaARotar.getY()));

	// Inicializar posicion de la entidad (se podria pasar a tick idealmente).
	entidadEnemigo->setPosicion(Vector(0, posDondeEmpiezaARotar.getY()));

	IAEnemigo* iaCircular = new IACircular(entidadEnemigo, jugadores, 0, false, Vector(1, factodModificadorRadioY), radio);
	IAEnemigo* iaHorizontal = new IAHorizontal2(entidadEnemigo, jugadores, true, posDondeEmpiezaARotar.getX(), iaCircular);

	this->innerIa = iaHorizontal;
}

IAEnemigo *IARotativaDesdeIzquierda::tick() {
	innerIa = innerIa->tick();
	return this;
}
