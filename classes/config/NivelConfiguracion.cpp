#include "NivelConfiguracion.h"
#include <string>

NivelConfiguracion::NivelConfiguracion(const std::list<FondoConfiguracion *> &fondos, EnemigosConfiguracion *enemigos, std::string finalNivel, float velocidad, float largo)
		: fondos(fondos), enemigos(enemigos), finalNivel(finalNivel), velocidad(velocidad), largo(largo) {}

const std::list<FondoConfiguracion *> &NivelConfiguracion::getFondos() const {
	return fondos;
}

EnemigosConfiguracion *NivelConfiguracion::getEnemigos() const {
	return enemigos;
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
