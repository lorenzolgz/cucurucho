#include <cstring>
#include "FondoConfiguracion.h"

FondoConfiguracion::FondoConfiguracion(const char* archivo, double velocidad) :
																					   velocidad(velocidad) {
    strcpy(arch, archivo);
}

double FondoConfiguracion::getVelocidad() const {
	return velocidad;
}

void FondoConfiguracion::setArchivo(char *archivo) const {
    strcpy(archivo, arch);
}

const char *FondoConfiguracion::getArchivo() const {
    return arch;
}