#include "SemillaEntidad.h"

SemillaEntidad::SemillaEntidad(Entidad* entidad, Vector posicion) {
	SemillaEntidad::entidad = entidad;
	SemillaEntidad::posicion = posicion;
}

Entidad *SemillaEntidad::getEntidad() {
	return entidad;
}

Vector SemillaEntidad::getPosicion() {
	return posicion;
}
