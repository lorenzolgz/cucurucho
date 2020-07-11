#include "IAEnemigoPatron2.h"

#define ATENUADOR_IA_2 0.8
#define DISTANCIA_ACTIVADORA_IA_2 300
#define DISTANCIA_DESACTIVADORA_IA_DERECHA_2 200
#define DISTANCIA_DESACTIVADORA_IA_IZQUIERDA_2 300

IAEnemigoPatron2::IAEnemigoPatron2(EntidadEnemigo *entidadEnemigo, std::map<int, Jugador*>* jugadores) {
	this->entidadEnemigo = entidadEnemigo;
	this->jugadores = jugadores;
}

IAEnemigo* IAEnemigoPatron2::tick() {
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

	if((!jugadorPorDerecha && distanciaMinima <= DISTANCIA_ACTIVADORA_IA_2 && distanciaMinima > DISTANCIA_DESACTIVADORA_IA_IZQUIERDA_2) ||
	   (jugadorPorDerecha && distanciaMinima <= DISTANCIA_ACTIVADORA_IA_2 && distanciaMinima > DISTANCIA_DESACTIVADORA_IA_DERECHA_2)) {

		float velocidadHorizontal = std::abs(entidadEnemigo->getVelocidadX()) * ATENUADOR_IA_2;
		float velocidadVertical = std::abs(entidadEnemigo->getVelocidadX()) * ATENUADOR_IA_2;

		if (jugadorPorDerecha)
			velocidadHorizontal = - velocidadHorizontal;

		if (jugadorPorArriba)
			velocidadVertical = - velocidadVertical;

		entidadEnemigo->setPosicion(Vector(entidadEnemigo->getPosicion().getX() + velocidadHorizontal, entidadEnemigo->getPosicion().getY() + velocidadVertical));
		l->debug("Posicion del Enemigo 02: "+ entidadEnemigo->getPosicion().getVector());

	} else if (distanciaMinima > DISTANCIA_ACTIVADORA_IA_2) {
		// Si ya se alejo lo suficiente tickeo como venia hasta encontrar otro jugador
		entidadEnemigo->innerTick();
	}

	return this;
}
