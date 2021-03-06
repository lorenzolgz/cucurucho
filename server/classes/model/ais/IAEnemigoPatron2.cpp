#include "IAEnemigoPatron2.h"

#define ATENUADOR_IA_2 0.8
#define DISTANCIA_ACTIVADORA_IA_2 300
#define DISTANCIA_DESACTIVADORA_IA_DERECHA_2 200
#define DISTANCIA_DESACTIVADORA_IA_IZQUIERDA_2 300
#define JUGADORES_NO_VIVOS_IA_2 99999
#define RANGO_DISPARO_MIN 400
#define RANGO_DISPARO_MAX 700

IAEnemigoPatron2::IAEnemigoPatron2(EntidadEnemigo *entidadEnemigo, std::map<int, Jugador*>* jugadores) {
	this->entidadEnemigo = entidadEnemigo;
	this->jugadores = jugadores;
}

IAEnemigo* IAEnemigoPatron2::tick() {
	Vector desplazamiento;
    float desplazamientoHor = JUGADORES_NO_VIVOS_IA_2;
    float desplazamientoVer = JUGADORES_NO_VIVOS_IA_2;
    float distanciaMinima = JUGADORES_NO_VIVOS_IA_2;
	bool jugadorPorDerecha;
	bool jugadorPorArriba;

    desplazamientoHor < 0 ? jugadorPorDerecha = true : jugadorPorDerecha = false;
	desplazamientoVer < 0 ? jugadorPorArriba = true : jugadorPorArriba = false;

	std::map<int, Jugador *>::iterator it;
	for (it = jugadores->begin(); it != jugadores->end(); it++) {
        // Solo itero a traves de los que estan vivos y conectados
        if(it->second->estaMuerto() || it->second->estaDesconectado())
            continue;
        desplazamiento = it->second->getPosicion() - entidadEnemigo->getPosicion();
        desplazamientoHor = desplazamiento.getX();
        desplazamientoVer = desplazamiento.getY();
        float distancia = desplazamiento.modulo();
        if (distancia < distanciaMinima) {
            distanciaMinima = distancia;
            desplazamientoHor < 0 ? jugadorPorDerecha = true : jugadorPorDerecha = false;
            desplazamientoVer < 0 ? jugadorPorArriba = true : jugadorPorArriba = false;
        }

        Vector direccion = entidadEnemigo->getCentroDeMasa() - it->second->getCentroDeMasa();
		if (direccion.modulo() > RANGO_DISPARO_MIN && direccion.modulo() < RANGO_DISPARO_MAX) {
			entidadEnemigo->disparar(direccion);
		}
	}

    if(distanciaMinima == JUGADORES_NO_VIVOS_IA_2){
        // Si no hay jugador vivo para perseguir solo tickean
        entidadEnemigo->setPosicion(Vector(entidadEnemigo->getPosicion().getX() - entidadEnemigo->getVelocidadX(), entidadEnemigo->getPosicion().getY()));
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

	} else if (distanciaMinima > DISTANCIA_ACTIVADORA_IA_2) {
		// Si ya se alejo lo suficiente tickeo como venia hasta encontrar otro jugador
		entidadEnemigo->setPosicion(Vector(entidadEnemigo->getPosicion().getX() - entidadEnemigo->getVelocidadX(), entidadEnemigo->getPosicion().getY()));
	}

	return this;
}
