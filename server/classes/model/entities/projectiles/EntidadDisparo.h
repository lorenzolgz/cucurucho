//
// Created by camix on 12/7/20.
//

#ifndef CUCURUCHO_ENTIDADDISPARO_H
#define CUCURUCHO_ENTIDADDISPARO_H


#include <list>
#include "../Forma.h"
#include "../Entidad.h"

class EntidadDisparo: public Entidad {
public:
	virtual struct EstadoDisparo state() = 0;
	virtual ~EntidadDisparo() {};

protected:

};


#endif //CUCURUCHO_ENTIDADDISPARO_H
