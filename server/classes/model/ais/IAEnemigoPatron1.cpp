#include "IAEnemigoPatron1.h"

#define ATENUADOR_IA_ENEMIGO_PATRON_1 0.65
#define DISTANCIA_ACTIVADORA_IA_ENEMIGO_PATRON_1 250
#define DISTANCIA_DESACTIVADORA_DERECHA_IA_ENEMIGO_PATRON_1 150
#define DISTANCIA_DESACTIVADORA_IZQUIERDA_IA_ENEMIGO_PATRON_1 80

IAEnemigoPatron1::IAEnemigoPatron1(EntidadEnemigo* entidadEnemigo, std::map<int, Jugador*>* jugadores) {
	this->entidadEnemigo = entidadEnemigo;
	this->jugadores = jugadores;
}

IAEnemigo* IAEnemigoPatron1::tick() {
	Vector desplazamiento = jugadores->at(0)->getPosicion() - entidadEnemigo->getPosicion();
	float desplazamientoHor = desplazamiento.getX();
	float desplazamientoVer = desplazamiento.getY();
	float distanciaMinima = desplazamiento.modulo();
	bool jugadorPorDerecha;
	bool jugadorPorArriba;

	desplazamientoHor < 0 ? jugadorPorDerecha = true : jugadorPorDerecha = false;
	desplazamientoVer < 0 ? jugadorPorArriba = true : jugadorPorArriba = false;

	std::map<int, Jugador *>::iterator it;
	for (it = jugadores->begin(); it != jugadores->end(); it++) {
		desplazamiento = it->second->getPosicion() - entidadEnemigo->getPosicion();
		desplazamientoHor = desplazamiento.getX();
		desplazamientoVer = desplazamiento.getY();
		float distancia = desplazamiento.modulo();
		if(distancia < distanciaMinima){
			distanciaMinima = distancia;
			desplazamientoHor < 0 ? jugadorPorDerecha = true : jugadorPorDerecha = false;
			desplazamientoVer < 0 ? jugadorPorArriba = true : jugadorPorArriba = false;
		}
	}

	if((!jugadorPorDerecha && distanciaMinima <= DISTANCIA_ACTIVADORA_IA_ENEMIGO_PATRON_1 && distanciaMinima > DISTANCIA_DESACTIVADORA_IZQUIERDA_IA_ENEMIGO_PATRON_1) ||
	   (jugadorPorDerecha && distanciaMinima <= DISTANCIA_ACTIVADORA_IA_ENEMIGO_PATRON_1 && distanciaMinima > DISTANCIA_DESACTIVADORA_DERECHA_IA_ENEMIGO_PATRON_1)) {

		float velocidadHorizontal = std::abs(entidadEnemigo->getVelocidadX()) * ATENUADOR_IA_ENEMIGO_PATRON_1;
		float velocidadVertical = std::abs(entidadEnemigo->getVelocidadX()) * ATENUADOR_IA_ENEMIGO_PATRON_1;

		if (jugadorPorDerecha)
			velocidadHorizontal = - velocidadHorizontal;

		if (jugadorPorArriba)
			velocidadVertical = - velocidadVertical;

		entidadEnemigo->setPosicion(Vector(entidadEnemigo->getPosicion().getX() + velocidadHorizontal, entidadEnemigo->getPosicion().getY() + velocidadVertical));

	} else if (distanciaMinima > DISTANCIA_ACTIVADORA_IA_ENEMIGO_PATRON_1) {
		// Si ya se alejo lo suficiente tickeo como venia hasta encontrar otro jugador
		entidadEnemigo->setPosicion(Vector(entidadEnemigo->getPosicion().getX() - entidadEnemigo->getVelocidadX(), entidadEnemigo->getPosicion().getY()));
	}

	return this;
}
