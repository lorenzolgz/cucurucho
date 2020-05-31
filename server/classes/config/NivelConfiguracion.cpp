#include "NivelConfiguracion.h"
#include <string>

NivelConfiguracion::NivelConfiguracion(EnemigosConfiguracion *enemigos, std::string finalNivel, float velocidad, float largo)
		: enemigos(enemigos), finalNivel(finalNivel), velocidad(velocidad), largo(largo) {}

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
