#ifndef CUCURUCHO_ENTIDADENEMIGO_H
#define CUCURUCHO_ENTIDADENEMIGO_H


#include "Entidad.h"

class EntidadEnemigo : public Entidad {
public:
	virtual struct EstadoEnemigo state() = 0;
};



#endif //CUCURUCHO_ENTIDADENEMIGO_H
