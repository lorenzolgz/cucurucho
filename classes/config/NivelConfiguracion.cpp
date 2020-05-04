#include "NivelConfiguracion.h"

NivelConfiguracion::NivelConfiguracion(const std::list<FondoConfiguracion *> &fondos, EnemigosConfiguracion *enemigos, std::string finalNivel)
		: fondos(fondos), enemigos(enemigos), finalNivel(finalNivel) {}

const std::list<FondoConfiguracion *> &NivelConfiguracion::getFondos() const {
	return fondos;
}

EnemigosConfiguracion *NivelConfiguracion::getEnemigos() const {
	return enemigos;
}

std::string NivelConfiguracion::getFinalNivel() const{
	return finalNivel;
}
