#include "Forma.h"

Forma::Forma(float posX, float posY, float ancho, float alto) {
	this->posX = posX;
	this->posY = posY;
	this->ancho = ancho;
	this->alto = alto;
}

bool Forma::colisiona(Forma otraForma) {
	Forma f1 = *this;
	Forma f2 = otraForma;

	return f1.getPosX() < f2.getPosX() + f2.getAncho() &&
		   f1.getPosX() + f1.getAncho() > f2.getPosX() &&
		   f1.getPosY() < f2.getPosY() + f2.getAlto() &&
		   f1.getPosY() + f1.getAlto() > f2.getPosY();
}

float Forma::getPosX() {
	return posX;
}

float Forma::getPosY() {
	return posY;
}

int Forma::getAncho() {
	return ancho;
}

int Forma::getAlto() {
	return alto;
}
