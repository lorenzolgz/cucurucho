//
// Created by javier on 19/7/20.
//

#ifndef CUCURUCHO_IAENEMIGOPATRON3EXT_H
#define CUCURUCHO_IAENEMIGOPATRON3EXT_H


#include "../EntidadEnemigo.h"
#include "default/IAOscilante.h"

class IAEnemigoPatron3Ext : public IAEnemigo {
public:
	IAEnemigoPatron3Ext(EntidadEnemigo *entidadEnemigo, std::map<int, Jugador *> *jugadores, EntidadEnemigo *padre,
			Vector posRelativa, Vector inferior, Vector superior);

	IAEnemigo* tick() override;

private:
	EntidadEnemigo *entidad;
	EntidadEnemigo *padre;
	std::map<int, Jugador*> *jugadores;
	int contador;
	Vector posRelativa;
	IAOscilante* iaMovimiento;
};


#endif //CUCURUCHO_IAENEMIGOPATRON3EXT_H
