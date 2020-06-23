#ifndef CUCURUCHO_NIVELCONFIGURACION_H
#define CUCURUCHO_NIVELCONFIGURACION_H

#include <list>
#include "FondoConfiguracion.h"

class NivelConfiguracion {
public:
	NivelConfiguracion(const std::list<FondoConfiguracion *> &fondos, std::string finalNivel, float velocidad, float largo);

	const std::list<FondoConfiguracion *> &getFondos() const;
	std::string getFinalNivel() const;
    float getVelocidad() const;
    float getLargo() const;

private:
	std::list<FondoConfiguracion*> fondos;
	std::string finalNivel;
	float velocidad;
	float largo;
};


#endif //CUCURUCHO_NIVELCONFIGURACION_H
