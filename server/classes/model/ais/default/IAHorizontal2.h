#ifndef CUCURUCHO_IAHORIZONTAL2_H
#define CUCURUCHO_IAHORIZONTAL2_H

#include "../IAEnemigo.h"
#include "../../Jugador.h"
#include "../../EntidadEnemigo.h"

class IAHorizontal2 : public IAEnemigo {
public:
	IAHorizontal2(EntidadEnemigo* entidadEnemigo, std::map<int, Jugador*>* jugadores, bool sentidoXPositivo, float posXFinal, IAEnemigo* next);

	IAEnemigo* tick() override;

private:
	EntidadEnemigo* entidadEnemigo;
	std::map<int, Jugador*>* jugadores;
	int ticks;
	float posXFinal;
	bool sentidoXPositivo;
	IAEnemigo* next;
};


#endif //CUCURUCHO_IAHORIZONTAL2_H
