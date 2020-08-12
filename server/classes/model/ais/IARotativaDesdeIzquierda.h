#ifndef CUCURUCHO_IAROTATIVADESDEIZQUIERDA_H
#define CUCURUCHO_IAROTATIVADESDEIZQUIERDA_H

#include <map>
#include "IAEnemigo.h"
#include "../EntidadEnemigo.h"
#include "default/IACircular.h"
#include "default/IAHorizontal2.h"

class IARotativaDesdeIzquierda  : public IAEnemigo {
public:
	IARotativaDesdeIzquierda(EntidadEnemigo *entidadEnemigo, std::map<int, Jugador *> *jugadores);
	~IARotativaDesdeIzquierda();

	IAEnemigo* tick() override;

private:
	EntidadEnemigo* entidadEnemigo;
	std::map<int, Jugador*>* jugadores;
	IAEnemigo *innerIa;
	int ticks;
	Vector factor;

	IACircular* iaCircular2;
	IAHorizontal2* iaHorizontalHaciaIzquierda;
	IACircular* iaCircular1;
	IAHorizontal2* iaHorizontalHaciaDerecha;
};


#endif //CUCURUCHO_IAROTATIVADESDEIZQUIERDA_H
