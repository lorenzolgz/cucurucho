#include "Entidad.h"

Vector Entidad::getPosicion() {
	return posicion;
}

int Entidad::getAncho() {
	return ancho;
}

int Entidad::getAlto() {
	return alto;
}

bool Entidad::colisiona(Entidad *otraEntidad) {
	std::list<Forma> formas1 = getFormas();
	std::list<Forma> formas2 = otraEntidad->getFormas();

	for (auto it1 = formas1.begin(); it1 != formas1.end(); it1++) {
		for (auto it2 = formas2.begin(); it2 != formas2.end(); it2++) {
			if ((*it1).colisiona(*it2)) {
				return true;
			}
		}
	}

	return false;
}

std::list<Forma> Entidad::getFormas() {
	std::list<Forma> formas;
	Forma formaSimple = Forma(getPosicion().getX(), getPosicion().getY(), getAncho(), getAlto());
	formas.emplace_back(formaSimple);
	return formas;
}

VidaEntidad *Entidad::getVidaEntidad() {
	return vida;
}

Vector Entidad::getCentroDeMasa() {
	return getPosicion() + Vector(getAncho() / 2, getAlto() / 2);
}
