#ifndef CUCURUCHO_IAENEMIGOPATRON3_H
#define CUCURUCHO_IAENEMIGOPATRON3_H


#include "IAEnemigo.h"
#include "../EntidadEnemigo.h"
#include "default/IAEstatico.h"
#include "default/IAHorizontal.h"
#include "default/IACircularHC.h"

class IAEnemigoPatron3 : public IAEnemigo {
public:
	IAEnemigoPatron3(EntidadEnemigo* entidadEnemigo, std::map<int, Jugador*>* jugadores);
	virtual ~IAEnemigoPatron3();

	IAEnemigo* tick() override;

private:
	EntidadEnemigo* entidadEnemigo;
	std::map<int, Jugador*>* jugadores;
	IAEnemigo* innerIa;

	IACircularHC* iaCircular;
	IAEstatico* iaEstatico;
	IAHorizontal* iaHorizontal;
};


#endif //CUCURUCHO_IAENEMIGOPATRON3_H
