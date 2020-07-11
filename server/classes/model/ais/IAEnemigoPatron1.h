#ifndef CUCURUCHO_IAENEMIGOPATRON1_H
#define CUCURUCHO_IAENEMIGOPATRON1_H


#include "IAEnemigo.h"
#include "../Jugador.h"
#include "../EntidadEnemigo.h"

class IAEnemigoPatron1 : public IAEnemigo {
public:
	IAEnemigoPatron1(EntidadEnemigo* entidadEnemigo, std::map<int, Jugador*>* jugadores);
	IAEnemigo* tick() override;

private:
	EntidadEnemigo* entidadEnemigo;
	std::map<int, Jugador*>* jugadores;
};


#endif //CUCURUCHO_IAENEMIGOPATRON1_H
