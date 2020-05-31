#ifndef CUCURUCHO_ESTADOCAMPOMOVIL_H
#define CUCURUCHO_ESTADOCAMPOMOVIL_H


#include <list>
#include "../../../commons/protocols/protocolo.h"

class EstadoCampoMovil {
public:
	struct EstadoJugador estadoJugador;
	std::list<EstadoEnemigo> estadosEnemigos;
};


#endif //CUCURUCHO_ESTADOCAMPOMOVIL_H
