#ifndef CUCURUCHO_PARTIDA_H
#define CUCURUCHO_PARTIDA_H


#include "ManagerNiveles.h"

class Partida {
public:
	Partida(Configuracion* config);
	void tick(struct Comando comandos[]);
    EstadoInternoNivel state(struct InformacionNivel* informacionNivel);

private:
	int nuevoNivel;
	std::map<int, Jugador*> jugadores;
	ManagerNiveles* managerNiveles;
};


#endif //CUCURUCHO_PARTIDA_H
