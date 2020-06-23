#include "FondoConfiguracion.h"

FondoConfiguracion::FondoConfiguracion(const std::string &archivo, double velocidad) : archivo(archivo),
																					   velocidad(velocidad) {}

const std::string &FondoConfiguracion::getArchivo() const {
	return archivo;
}

double FondoConfiguracion::getVelocidad() const {
	return velocidad;
}
