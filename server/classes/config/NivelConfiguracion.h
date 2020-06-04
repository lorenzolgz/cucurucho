#ifndef CUCURUCHO_NIVELCONFIGURACION_H
#define CUCURUCHO_NIVELCONFIGURACION_H

#include <list>
#include <string>
#include "EnemigosConfiguracion.h"
#include "../../../classes/config/FondoConfiguracion.h"

class NivelConfiguracion {
public:

    NivelConfiguracion(std::list<FondoConfiguracion *> fondos, EnemigosConfiguracion *enemigos, const char *finalNivel,
                       float velocidad, float largo);

    EnemigosConfiguracion *getEnemigos() const;
    float getVelocidad() const;
    float getLargo() const;
    const std::list<FondoConfiguracion *> &getFondos() const;
    void getFinalNivel(char *final) const;
    const char *getFinalNivel() const;

private:

    std::list<FondoConfiguracion*> fondos;
	EnemigosConfiguracion* enemigos;
	char finalNivel[255];
	float velocidad;
	float largo;

};


#endif //CUCURUCHO_NIVELCONFIGURACION_H
