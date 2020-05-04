#include "NivelConfiguracion.h"

NivelConfiguracion::NivelConfiguracion(const std::list<FondoConfiguracion *> &fondos, EnemigosConfiguracion *enemigos)
		: fondos(fondos), enemigos(enemigos) {}

const std::list<FondoConfiguracion *> &NivelConfiguracion::getFondos() const {
	return fondos;
}

EnemigosConfiguracion *NivelConfiguracion::getEnemigos() const {
	return enemigos;
}
