#ifndef CUCURUCHO_IAHORIZONTAL_H
#define CUCURUCHO_IAHORIZONTAL_H


#include "../IAEnemigo.h"
#include "../../Jugador.h"
#include "../../EntidadEnemigo.h"

// Viene de derecha a izquierda, hasta dejar un margen a la derecha entre donde termina la entidadEnemigo y el fin del campo.
class IAHorizontal : public IAEnemigo {
public:
	IAHorizontal(EntidadEnemigo* entidadEnemigo, std::map<int, Jugador*>* jugadores, float margenDerecho, IAEnemigo* next);

	IAEnemigo* tick() override;

private:
	EntidadEnemigo* entidadEnemigo;
	std::map<int, Jugador*>* jugadores;
	float margenDerecho;
	IAEnemigo* next;
};


#endif //CUCURUCHO_IAHORIZONTAL_H
