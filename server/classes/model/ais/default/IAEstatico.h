#ifndef CUCURUCHO_IAESTATICO_H
#define CUCURUCHO_IAESTATICO_H


#include "../IAEnemigo.h"
#include "../../EntidadEnemigo.h"

class IAEstatico : public IAEnemigo {
public:
	IAEstatico(EntidadEnemigo* entidadEnemigo, std::map<int, Jugador*>* jugadores, int maxTicks, IAEnemigo* next);

	IAEnemigo* tick() override;

private:
	EntidadEnemigo* entidadEnemigo;
	std::map<int, Jugador*>* jugadores;
	int ticks;
	int maxTicks;
	IAEnemigo* next;
};


#endif //CUCURUCHO_IAESTATICO_H
