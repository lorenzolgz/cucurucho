#ifndef CUCURUCHO_IAHORIZONTAL_H
#define CUCURUCHO_IAHORIZONTAL_H


#include "../IAEnemigo.h"
#include "../../Jugador.h"
#include "../../EntidadEnemigo.h"

class IAHorizontal : public IAEnemigo {
public:
	IAHorizontal(EntidadEnemigo* entidadEnemigo, std::map<int, Jugador*>* jugadores, float paddingIzquierdo, IAEnemigo* next);

	IAEnemigo* tick() override;

private:
	EntidadEnemigo* entidadEnemigo;
	std::map<int, Jugador*>* jugadores;
	float paddingIzquierdo;
	IAEnemigo* next;
};


#endif //CUCURUCHO_IAHORIZONTAL_H
