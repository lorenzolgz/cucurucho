#include "IAEnemigoPatron1.h"

#define RANGO_DISPARO_MIN 400
#define RANGO_DISPARO_MAX 700
#define RANGO_PERSEGUIR 400
#define RANGO_PERSEGUIR_LENTO 200
#define RANGO_PERSEGUIR_LENTO_MINIMO 100

IAEnemigoPatron1::IAEnemigoPatron1(EntidadEnemigo* entidadEnemigo, std::map<int, Jugador*>* jugadores) {
	this->entidadEnemigo = entidadEnemigo;
	this->jugadores = jugadores;
}

IAEnemigo* IAEnemigoPatron1::tick() {

	Jugador* jugadorMasCercano = nullptr;

	std::map<int, Jugador *>::iterator it;
	for (it = jugadores->begin(); it != jugadores->end(); it++) {
        // Solo itero a traves de los que estan vivos y conectados
        if(it->second->estaMuerto() || it->second->estaDesconectado())
            continue;

		Vector direccion = entidadEnemigo->getCentroDeMasa() - it->second->getCentroDeMasa();
		if (direccion.modulo() < RANGO_PERSEGUIR) {
			if (jugadorMasCercano == nullptr) {
				jugadorMasCercano = it->second;
			} else {
				Vector direccionMasCercano = entidadEnemigo->getCentroDeMasa() - jugadorMasCercano->getCentroDeMasa();
				if (direccionMasCercano.modulo() > direccion.modulo()) {
					jugadorMasCercano = it->second;
				}
			}
		}
	}

	if (jugadorMasCercano == nullptr) {
        // Si no hay jugador vivo cercano para perseguir solo tickean
        entidadEnemigo->setPosicion(entidadEnemigo->getPosicion() - Vector(entidadEnemigo->getVelocidadX(), 0));
        return this;
	}

	Vector direccion = jugadorMasCercano->getCentroDeMasa() - entidadEnemigo->getCentroDeMasa();
	Vector velocidad = direccion.escalar(entidadEnemigo->getVelocidadX());
	if (direccion.modulo() < RANGO_PERSEGUIR_LENTO) {
		// Para darle al jugador una posibilidad de escapar, se reduce la velocidad del enemigo
		if (direccion.modulo() < RANGO_PERSEGUIR_LENTO_MINIMO) {
			velocidad = velocidad / 2;
		} else {
			velocidad = velocidad * (direccion.modulo() / 2 + RANGO_PERSEGUIR_LENTO / 2 - RANGO_PERSEGUIR_LENTO_MINIMO);
			velocidad = velocidad / (RANGO_PERSEGUIR_LENTO - RANGO_PERSEGUIR_LENTO_MINIMO);
		}
	}
	entidadEnemigo->setPosicion(entidadEnemigo->getPosicion() - velocidad);
	entidadEnemigo->disparar(direccion * -1);

	return this;
}
