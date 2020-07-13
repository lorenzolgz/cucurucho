#include "EnemigoFinal1.h"
#include "ais/IAEnemigoPatron3.h"
#include "life/VidaEnemigoFinal1.h"

EnemigoFinal1::EnemigoFinal1(float x, float y, float velocidadX, std::map<int, Jugador*>* jugadores) {
	this->posicion = Vector(x, y);
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

Vector EnemigoFinal1::getPosicion() {
	return posicion;
}

int EnemigoFinal1::getAncho() {
	return ENEMIGO_FINAL1_ANCHO;
}

int EnemigoFinal1::getAlto() {
	return ENEMIGO_FINAL1_ALTO;
}

int EnemigoFinal1::getTipoEntidad() {
	return ENTIDAD_ENEMIGO_FINAL1;
}

std::list<Forma> EnemigoFinal1::getFormas() {
	std::list<Forma> formas;
	Forma formaSimple = Forma(getPosicion().getX(), getPosicion().getY(), getAncho(), getAlto());
	formas.emplace_back(formaSimple);
	return formas;
}

VidaEntidad *EnemigoFinal1::getVidaEntidad() {
	return vida;
}

void EnemigoFinal1::disparar() {

}
