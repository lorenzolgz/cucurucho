#include "NivelConfiguracion.h"
#include <string>

NivelConfiguracion::NivelConfiguracion(const std::list<FondoConfiguracion *> &fondos, std::string finalNivel, float velocidad, float largo)
		: fondos(fondos), finalNivel(finalNivel), velocidad(velocidad), largo(largo) {}

const std::list<FondoConfiguracion *> &NivelConfiguracion::getFondos() const {
	return fondos;
}

std::string NivelConfiguracion::getFinalNivel() const{
	return finalNivel;
}

float NivelConfiguracion::getVelocidad() const {
    return velocidad;
}

float NivelConfiguracion::getLargo() const {
    return largo;
}
