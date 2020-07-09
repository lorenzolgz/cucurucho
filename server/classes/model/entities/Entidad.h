#ifndef CUCURUCHO_ENTIDAD_H
#define CUCURUCHO_ENTIDAD_H

#include <list>
#include "../Ticker.h"
#include "Forma.h"
#include "../life/VidaEntidad.h"

class Ticker;

// Todo: Pasar a commons y reemplazar donde se usa 1 o 2 en los switchs !!!!
enum {
	ENTIDAD_JUGADOR,
	ENTIDAD_ENEMIGO1,
	ENTIDAD_ENEMIGO2
};

class Entidad : public Ticker {
public:
	virtual int getAncho() = 0;
	virtual int getAlto() = 0;
	virtual Vector getPosicion() = 0;
	virtual int getTipoEntidad() = 0;
	virtual std::list<Forma> getFormas() = 0;
	virtual VidaEntidad* getVidaEntidad() = 0;
	bool colisiona(Entidad* otraEntidad);
};


#endif //CUCURUCHO_ENTIDAD_H
