//
// Created by javier on 19/7/20.
//

#ifndef CUCURUCHO_IAOSCILANTE_H
#define CUCURUCHO_IAOSCILANTE_H


#include "../IAEnemigo.h"
#include "../../EntidadEnemigo.h"

class IAOscilante : public IAEnemigo {
public:

	IAOscilante(EntidadEnemigo* entidadEnemigo, Vector inferior, Vector superior);

	IAEnemigo* tick() override;

	void setPosInicial(const Vector &posInicial);

private:
	EntidadEnemigo* entidadEnemigo;
	std::map<int, Jugador*>* jugadores;
	Vector inferior;
	Vector superior;
	Vector posInicial;
	int contador;
};


#endif //CUCURUCHO_IAOSCILANTE_H
