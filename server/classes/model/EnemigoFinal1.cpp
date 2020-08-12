#include "EnemigoFinal1.h"
#include "ais/IAEnemigoPatron3.h"
#include "life/VidaEnemigoFinal1.h"
#include "EnemigoFinal1Ext.h"

EnemigoFinal1::EnemigoFinal1(float x, float y, float velocidadX, std::map<int, Jugador*>* jugadores, CampoMovil* campo) {
	this->posicion = Vector(x, y);
	this->ancho = ENEMIGO_FINAL1_ANCHO;
	this->alto = ENEMIGO_FINAL1_ALTO;
	this->velocidadX = velocidadX;
	this->vida = new VidaEnemigoFinal1();
	this->ia = new IAEnemigoPatron3(this, jugadores);
	this->campo = campo;

	crearExtensiones(jugadores);
	l->info("Se creo correctamente el Enemigo Final 1.");
}

void EnemigoFinal1::crearExtensiones(std::map<int, Jugador*>* jugadores) {
	Vector posRelativa, inferior, superior;

	// Al frente del enemigo
	posRelativa = Vector(-ENEMIGO_FINAL1_ANCHO, 0);
	inferior = Vector(0, - ENEMIGO_FINAL1_ALTO / 2);
	superior = Vector(0, ENEMIGO_FINAL1_ALTO / 2);
	this->extensiones.push_back(new EnemigoFinal1Ext(jugadores, campo, this, posRelativa, inferior, superior));

	// Arriba del enemigo
	posRelativa = Vector(- ENEMIGO_FINAL1_ANCHO / 2, - ENEMIGO_FINAL1_ALTO * 2 / 3);
	inferior = Vector(ENEMIGO_FINAL1_ALTO / 4, - ENEMIGO_FINAL1_ALTO / 5);
	superior = Vector(- ENEMIGO_FINAL1_ALTO / 4, ENEMIGO_FINAL1_ALTO / 4);
	this->extensiones.push_back(new EnemigoFinal1Ext(jugadores, campo, this, posRelativa, inferior, superior));

	// Abajo del enemigo
	posRelativa = Vector(- ENEMIGO_FINAL1_ANCHO / 2, ENEMIGO_FINAL1_ALTO * 2 / 3);
	inferior = Vector(- ENEMIGO_FINAL1_ALTO / 4, - ENEMIGO_FINAL1_ALTO / 4);
	superior = Vector(ENEMIGO_FINAL1_ALTO / 4, ENEMIGO_FINAL1_ALTO / 5);
	this->extensiones.push_back(new EnemigoFinal1Ext(jugadores, campo, this, posRelativa, inferior, superior));
}

EstadoEnemigo EnemigoFinal1::state() {
	struct EstadoEnemigo estado;
	estado.posicionX = posicion.getX();
	estado.posicionY = posicion.getY();
	estado.energia = vida->getEnergia();
	estado.clase = 3;
	return estado;
}

std::list<EntidadEnemigo*> EnemigoFinal1::getExtensiones() {
	return extensiones;
}

std::list<Forma> EnemigoFinal1::getFormas() {
	std::list<Forma> formas;
	formas.emplace_back(Forma(getPosicion().getX(), getPosicion().getY() + getAncho() / 3.28,
							  getAncho() / 4.80, getAncho() / 4.80));
	formas.emplace_back(Forma(getPosicion().getX() + getAncho() / 6.57, getPosicion().getY() + getAlto() / 3.42,
							  getAncho() / 4.16, getAncho() / 4.16));
	formas.emplace_back(Forma(getPosicion().getX() + getAncho() / 3.90, getPosicion().getY() + getAlto() / 6,
							  getAlto() / 1.6, getAlto() / 1.6));
	formas.emplace_back(Forma(getPosicion().getX() + getAncho() / 2.90, getPosicion().getY() + getAlto() / 32,
							  getAncho() / 1.52, getAncho() / 1.52));
	return formas;
}
float EnemigoFinal1::getVelocidadX() {
	return velocidadX;
}

void EnemigoFinal1::setPosicion(Vector nuevaPosicion) {
	posicion = nuevaPosicion;
}

void EnemigoFinal1::tick() {
	ia = ia->tick();

	// Si esta muerto, matar las extensiones
	if (this->vida->estaMuerto()) {
		for (EntidadEnemigo* extension : extensiones) {
			// TODO: esto es como si hubiera muerto, pero deberia haber un metodo "suicidarse"
			extension->getVidaEntidad()->procesarColision(ENTIDAD_JUGADOR);
		}
	}
}

int EnemigoFinal1::getTipoEntidad() {
	return ENTIDAD_ENEMIGO_FINAL1;
}

void EnemigoFinal1::disparar(Vector vector) {
	// pass
}

EnemigoFinal1::~EnemigoFinal1() {
	delete this->vida;
	delete this->ia;

	for (auto* extension : this->extensiones) {
		delete extension;
	}
}
