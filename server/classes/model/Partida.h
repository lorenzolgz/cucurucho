//
// Created by rodrigosouto on 31/5/20.
//

#ifndef CUCURUCHO_PARTIDA_H
#define CUCURUCHO_PARTIDA_H


#include "ManagerNiveles.h"

class Partida {
public:
	Partida(Configuracion* config);

	void tick(struct Command command);

private:
	Jugador* jugador;
	ManagerNiveles* managerNiveles;
};


#endif //CUCURUCHO_PARTIDA_H
