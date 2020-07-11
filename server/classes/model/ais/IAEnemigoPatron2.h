#ifndef CUCURUCHO_IAENEMIGOPATRON2_H
#define CUCURUCHO_IAENEMIGOPATRON2_H


#include "IAEnemigo.h"
#include "../Jugador.h"
#include "../EntidadEnemigo.h"

class IAEnemigoPatron2 : public IAEnemigo {
public:
	IAEnemigoPatron2(EntidadEnemigo* entidadEnemigo, std::map<int, Jugador*>* jugadores);

	IAEnemigo* tick() override;

private:
	EntidadEnemigo* entidadEnemigo;
	std::map<int, Jugador*>* jugadores;
};


#endif //CUCURUCHO_IAENEMIGOPATRON2_H
