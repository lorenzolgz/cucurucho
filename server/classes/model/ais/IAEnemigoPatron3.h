#ifndef CUCURUCHO_IAENEMIGOPATRON3_H
#define CUCURUCHO_IAENEMIGOPATRON3_H


#include "IAEnemigo.h"
#include "../EntidadEnemigo.h"

class IAEnemigoPatron3 : public IAEnemigo {
public:
	IAEnemigoPatron3(EntidadEnemigo* entidadEnemigo, std::map<int, Jugador*>* jugadores);

	IAEnemigo* tick() override;

private:
	EntidadEnemigo* entidadEnemigo;
	std::map<int, Jugador*>* jugadores;
	IAEnemigo* innerIa;
};


#endif //CUCURUCHO_IAENEMIGOPATRON3_H
