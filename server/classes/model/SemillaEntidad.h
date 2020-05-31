#ifndef CUCURUCHO_SEMILLAENTIDAD_H
#define CUCURUCHO_SEMILLAENTIDAD_H


#include "../../../commons/utils/Vector.h"

class Entidad;

class SemillaEntidad {
public:
	SemillaEntidad(Entidad* entidad, Vector posicion);
	Entidad* getEntidad();
	Vector getPosicion();

private:
	Entidad* entidad;
	Vector posicion;
};


#endif //CUCURUCHO_SEMILLAENTIDAD_H
