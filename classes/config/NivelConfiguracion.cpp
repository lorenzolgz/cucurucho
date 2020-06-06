#include "NivelConfiguracion.h"
#include <string>
#include <utility>

NivelConfiguracion::NivelConfiguracion(std::list<FondoConfiguracion *> fondos, EnemigosConfiguracion *enemigos, const char* finalNivel, float velocidad, float largo)
		: fondos(std::move(fondos)), enemigos(enemigos), finalNivel(finalNivel), velocidad(velocidad), largo(largo) {}

const std::list<FondoConfiguracion *> &NivelConfiguracion::getFondos() const {
	return fondos;
}

EnemigosConfiguracion *NivelConfiguracion::getEnemigos() const {
	return enemigos;
}

const char* NivelConfiguracion::getFinalNivel() const{
	return finalNivel;
}

float NivelConfiguracion::getVelocidad() const {
    return velocidad;
}

float NivelConfiguracion::getLargo() const {
    return largo;
}
