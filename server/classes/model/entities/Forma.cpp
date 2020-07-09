#include "Forma.h"

Forma::Forma(float posX, float posY, float ancho, float alto) {
	this->posX = posX;
	this->posY = posY;
	this->ancho = ancho;
	this->alto = alto;
}

float Forma::getPosX() {
	return posX;
}

float Forma::getPosY() {
	return posY;
}

float Forma::getAncho() {
	return ancho;
}

float Forma::getAlto() {
	return alto;
}
