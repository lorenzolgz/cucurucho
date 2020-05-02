//
// Created by rodrigosouto on 2/5/20.
//

#ifndef CUCURUCHO_NIVELCONFIGURACION_H
#define CUCURUCHO_NIVELCONFIGURACION_H

#include <list>
#include "EnemigosConfiguracion.h"
#include "FondoConfiguracion.h"

class NivelConfiguracion {
public:
	NivelConfiguracion(const std::list<FondoConfiguracion *> &fondos, EnemigosConfiguracion *enemigos);

	const std::list<FondoConfiguracion *> &getFondos() const;
	EnemigosConfiguracion *getEnemigos() const;

private:
	std::list<FondoConfiguracion*> fondos;
	EnemigosConfiguracion* enemigos;
};


#endif //CUCURUCHO_NIVELCONFIGURACION_H
