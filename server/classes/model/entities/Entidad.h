#ifndef CUCURUCHO_ENTIDAD_H
#define CUCURUCHO_ENTIDAD_H

#include <list>
#include "../Ticker.h"
#include "Forma.h"
#include "../life/VidaEntidad.h"
#include "../../../../commons/utils/Vector.h"


// Todo: Pasar a commons y reemplazar donde se usa 1 o 2 en los switchs !!!!
enum {
	ENTIDAD_JUGADOR,
	ENTIDAD_ENEMIGO1,
	ENTIDAD_ENEMIGO2,
    ENTIDAD_DISPARO_JUGADOR,
    ENTIDAD_DISPARO_ENEMIGO1,
    ENTIDAD_DISPARO_ENEMIGO2,
	ENTIDAD_ENEMIGO_FINAL1,
	ENTIDAD_ENEMIGO_FINAL1EXT
};

class Entidad : public Ticker {
public:
	Vector getPosicion();
	Vector getCentroDeMasa();
	int getAncho();
	int getAlto();
	virtual std::list<Forma> getFormas();
	virtual VidaEntidad* getVidaEntidad();
	bool colisiona(Entidad* otraEntidad);
	virtual int getTipoEntidad() = 0;

protected:
	Vector posicion;
	Vector posicionRelativa;
	float ancho;
	float alto;
	VidaEntidad* vida;
};


#endif //CUCURUCHO_ENTIDAD_H
