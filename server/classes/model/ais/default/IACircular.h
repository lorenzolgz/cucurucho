#ifndef CUCURUCHO_IACIRCULAR_H
#define CUCURUCHO_IACIRCULAR_H


#include <map>
#include "../IAEnemigo.h"
#include "../../EntidadEnemigo.h"

class IACircular : public IAEnemigo {
public:
	IACircular(EntidadEnemigo* entidadEnemigo, std::map<int, Jugador*>* jugadores, Vector factor, float radio);

	IAEnemigo* tick() override;

private:
	EntidadEnemigo* entidadEnemigo;
	std::map<int, Jugador*>* jugadores;
	bool primerTick;
	int ticks;
	Vector eje;
	float radio;
	Vector factor;
};


#endif //CUCURUCHO_IACIRCULAR_H
