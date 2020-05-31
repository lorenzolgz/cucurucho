#ifndef CUCURUCHO_ESTADOINTERNOCAMPOMOVIL_H
#define CUCURUCHO_ESTADOINTERNOCAMPOMOVIL_H


#include <list>
#include "../../../commons/protocols/protocolo.h"

class EstadoInternoCampoMovil {
public:
	struct EstadoJugador estadoJugador;
	std::list<EstadoEnemigo> estadosEnemigos;
};


#endif //CUCURUCHO_ESTADOINTERNOCAMPOMOVIL_H
