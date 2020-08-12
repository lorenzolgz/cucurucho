#ifndef CUCURUCHO_IACIRCULARHC_H
#define CUCURUCHO_IACIRCULARHC_H


#include <map>
#include "../IAEnemigo.h"
#include "../../EntidadEnemigo.h"

// HC por hardcodeada, quedo muy acoplada la posicion de los EnemigoFinalExt a la del EnemigoFinal, haciendo que no se pueda modificar esta clase asi nomas
class IACircularHC : public IAEnemigo {
public:
	IACircularHC(EntidadEnemigo* entidadEnemigo, std::map<int, Jugador*>* jugadores, Vector factor, float radio);

	IAEnemigo* tick() override;

private:
	EntidadEnemigo* entidadEnemigo;
	std::map<int, Jugador*>* jugadores;
	bool primerTick;
	int ticks;
	Vector eje;
	float radio;
	Vector factor;
};


#endif //CUCURUCHO_IACIRCULARHC_H
