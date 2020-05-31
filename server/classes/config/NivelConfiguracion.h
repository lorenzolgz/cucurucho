#ifndef CUCURUCHO_NIVELCONFIGURACION_H
#define CUCURUCHO_NIVELCONFIGURACION_H

#include <list>
#include <string>
#include "EnemigosConfiguracion.h"

class NivelConfiguracion {
public:
	NivelConfiguracion(EnemigosConfiguracion *enemigos, std::string finalNivel, float velocidad, float largo);

	EnemigosConfiguracion *getEnemigos() const;
	std::string getFinalNivel() const;
    float getVelocidad() const;
    float getLargo() const;

private:
	EnemigosConfiguracion* enemigos;
	std::string finalNivel;
	float velocidad;
	float largo;
};


#endif //CUCURUCHO_NIVELCONFIGURACION_H
