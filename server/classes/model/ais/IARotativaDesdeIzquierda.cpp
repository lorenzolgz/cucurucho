#include "math.h"
#include "IARotativaDesdeIzquierda.h"
#include "default/IACircular.h"
#include "default/IAHorizontal.h"
#include "default/IAHorizontal2.h"
#include "../../../../commons/utils/Constantes.h"

IARotativaDesdeIzquierda::IARotativaDesdeIzquierda(EntidadEnemigo *entidadEnemigo, std::map<int, Jugador *> *jugadores) {
	this->entidadEnemigo = entidadEnemigo;
	this->jugadores = jugadores;
	this->primerTick = true;
	this->ticks = 0;

	float minimoMargenY = 20 + random() % 30;
	float factodModificadorRadioY = 0.40 + random() % 15 / 100;
	float margenDerecho = 50 + random() % 200;
	float radio = 120 + random() % 20;
	float posXDondeEmpiezaARotarPrimerCirculo = CAMPO_ANCHO - margenDerecho - entidadEnemigo->getAncho();
	float posYDondeEmpiezaARotarPrimerCirculo = (minimoMargenY + radio * factodModificadorRadioY) +
			random() % (long) (floor(1.0 * CAMPO_ALTO - entidadEnemigo->getAlto() - 2 * radio * factodModificadorRadioY - minimoMargenY));
	Vector posDondeEmpiezaARotarPrimerCirculo = Vector(posXDondeEmpiezaARotarPrimerCirculo, posYDondeEmpiezaARotarPrimerCirculo);

	// Inicializar posicion de la entidad (se podria pasar a tick idealmente).
	entidadEnemigo->setPosicion(Vector(0, posDondeEmpiezaARotarPrimerCirculo.getY()));

	float posXDondeEmpiezaARotarSegundoCirculo = margenDerecho + 2 * radio;

	IACircular* iaCircular2 = new IACircular(entidadEnemigo, jugadores, 0, false, Vector(1, factodModificadorRadioY), radio, 720, nullptr);
	IAEnemigo* iaHorizontalHaciaIzquierda = new IAHorizontal2(entidadEnemigo, jugadores, false, posXDondeEmpiezaARotarSegundoCirculo, iaCircular2);
	IAEnemigo* iaCircular1 = new IACircular(entidadEnemigo, jugadores, 0, false, Vector(1, factodModificadorRadioY), radio, 540, iaHorizontalHaciaIzquierda);
	IAEnemigo* iaHorizontalHaciaDerecha = new IAHorizontal2(entidadEnemigo, jugadores, true, posDondeEmpiezaARotarPrimerCirculo.getX(), iaCircular1);
	iaCircular2->setNext(iaHorizontalHaciaDerecha);

	this->innerIa = iaHorizontalHaciaDerecha;
}

IAEnemigo *IARotativaDesdeIzquierda::tick() {
	innerIa = innerIa->tick();
	return this;
}
