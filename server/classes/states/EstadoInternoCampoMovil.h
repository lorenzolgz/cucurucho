#ifndef CUCURUCHO_ESTADOINTERNOCAMPOMOVIL_H
#define CUCURUCHO_ESTADOINTERNOCAMPOMOVIL_H


#include <list>
#include "../../../commons/protocols/protocolo.h"

class EstadoInternoCampoMovil {
public:
	int posX;
	std::list<EstadoEnemigo> estadosEnemigos;
	std::list<EstadoJugador> estadosJugadores;
    std::list<EstadoDisparo> estadosDisparos;
    std::list<EstadoDisparo> estadosDisparosEnemigos;

};


#endif //CUCURUCHO_ESTADOINTERNOCAMPOMOVIL_H
