#include "EnemigoFinal1.h"
#include "ais/IAEnemigoPatron3.h"
#include "life/VidaEnemigoFinal1.h"

EnemigoFinal1::EnemigoFinal1(float x, float y, float velocidadX, std::map<int, Jugador*>* jugadores) {
	this->posicion = Vector(x, y);
	this->ancho = ENEMIGO_FINAL1_ANCHO;
	this->alto = ENEMIGO_FINAL1_ALTO;
	this->velocidadX = velocidadX;
	this->vida = new VidaEnemigoFinal1();
	this->ia = new IAEnemigoPatron3(this, jugadores);
	l->info("Se creo correctamente el Enemigo 01.");
}

EstadoEnemigo EnemigoFinal1::state() {
	struct EstadoEnemigo estado;
	estado.posicionX = posicion.getX();
	estado.posicionY = posicion.getY();
	estado.clase = 3;
	return estado;
}

float EnemigoFinal1::getVelocidadX() {
	return velocidadX;
}

void EnemigoFinal1::setPosicion(Vector nuevaPosicion) {
	posicion = nuevaPosicion;
}

void EnemigoFinal1::tick() {
	ia = ia->tick();
}

int EnemigoFinal1::getTipoEntidad() {
	return ENTIDAD_ENEMIGO_FINAL1;
}

void EnemigoFinal1::disparar(Vector vector) {
	// pass
}
