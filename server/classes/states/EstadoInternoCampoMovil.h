#ifndef CUCURUCHO_ESTADOINTERNOCAMPOMOVIL_H
#define CUCURUCHO_ESTADOINTERNOCAMPOMOVIL_H


#include <list>
#include "../../../commons/protocols/protocolo.h"

class EstadoInternoCampoMovil {
public:
	std::list<EstadoEnemigo> estadosEnemigos;
    std::list<EstadoJugador> estadosJugadores;
};


#endif //CUCURUCHO_ESTADOINTERNOCAMPOMOVIL_H
