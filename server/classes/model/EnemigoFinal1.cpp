#include "EnemigoFinal1.h"
#include "life/VidaEnemigo1.h"

EnemigoFinal1::EnemigoFinal1(float x, float y, float velocidadX) {
	this->posicion = Vector(x, y);
	this->velocidadX = velocidadX; // Posición 2 de sprite
	// !!!!!
	this->vida = new VidaEnemigo1();
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
	return 0;
}

void EnemigoFinal1::setPosicion(Vector nuevaPosicion) {
	posicion = nuevaPosicion;
}

void EnemigoFinal1::innerTick() {

}

void EnemigoFinal1::tick() {
	posicion = posicion - Vector(velocidadX, 0);
}

Vector EnemigoFinal1::getPosicion() {
	return posicion;
}

int EnemigoFinal1::getAncho() {
	return 1;
}

int EnemigoFinal1::getAlto() {
	return 1;
}

int EnemigoFinal1::getTipoEntidad() {
	return ENTIDAD_ENEMIGO_FINAL1;
}

std::list<Forma> EnemigoFinal1::getFormas() {
	return std::list<Forma>();
}

VidaEntidad *EnemigoFinal1::getVidaEntidad() {
	return vida;
}
