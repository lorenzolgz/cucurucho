#include "NivelConfiguracion.h"
#include <string>
#include <iostream>
#include <cstring>

NivelConfiguracion::NivelConfiguracion(std::list<FondoConfiguracion *> fondos, EnemigosConfiguracion *enemigos, const char* finalNivel, float velocidad, float largo)
		: fondos(fondos), enemigos(enemigos), velocidad(velocidad), largo(largo) {
    strcpy(NivelConfiguracion::finalNivel, finalNivel);
}

EnemigosConfiguracion *NivelConfiguracion::getEnemigos() const {
	return enemigos;
}

void NivelConfiguracion::getFinalNivel(char* final) const{
    strcpy(final, finalNivel);
}

const char* NivelConfiguracion::getFinalNivel() const {
    return finalNivel;
}

float NivelConfiguracion::getVelocidad() const {
    return velocidad;
}

float NivelConfiguracion::getLargo() const {
    return largo;
}

const std::list<FondoConfiguracion *> &NivelConfiguracion::getFondos() const {
    return fondos;
}
