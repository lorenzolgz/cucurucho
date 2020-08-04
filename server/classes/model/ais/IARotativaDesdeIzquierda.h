#ifndef CUCURUCHO_IAROTATIVADESDEIZQUIERDA_H
#define CUCURUCHO_IAROTATIVADESDEIZQUIERDA_H

#include <map>
#include "IAEnemigo.h"
#include "../EntidadEnemigo.h"

class IARotativaDesdeIzquierda  : public IAEnemigo {
public:
	IARotativaDesdeIzquierda(EntidadEnemigo *entidadEnemigo, std::map<int, Jugador *> *jugadores);

	IAEnemigo* tick() override;

private:
	EntidadEnemigo* entidadEnemigo;
	std::map<int, Jugador*>* jugadores;
	IAEnemigo *innerIa;
	bool primerTick;
	int ticks;
	Vector eje;
	float radio;
	Vector factor;
};


#endif //CUCURUCHO_IAROTATIVADESDEIZQUIERDA_H
