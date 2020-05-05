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
	NivelConfiguracion(const std::list<FondoConfiguracion *> &fondos, EnemigosConfiguracion *enemigos, std::string finalNivel, float velocidad, float largo);

	const std::list<FondoConfiguracion *> &getFondos() const;
	EnemigosConfiguracion *getEnemigos() const;
	std::string getFinalNivel() const;
    float getVelocidad() const;
    float getLargo() const;

private:
	std::list<FondoConfiguracion*> fondos;
	EnemigosConfiguracion* enemigos;
	std::string finalNivel;
	float velocidad;
	float largo;
};


#endif //CUCURUCHO_NIVELCONFIGURACION_H
