#ifndef CUCURUCHO_ENTIDAD_H
#define CUCURUCHO_ENTIDAD_H


#include "Ticker.h"
class Ticker;

enum {
	JUGADOR,
	ENEMIGO1,
	ENEMIGO2
};

class Entidad : public Ticker {
public:
	virtual int getAncho() = 0;
	virtual int getAlto() = 0;
	virtual Vector getPosicion() = 0;
};


#endif //CUCURUCHO_ENTIDAD_H
