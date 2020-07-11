#ifndef CUCURUCHO_ENTIDADENEMIGO_H
#define CUCURUCHO_ENTIDADENEMIGO_H


#include "entities/Entidad.h"
#include "Jugador.h"
#include "../../../commons/utils/Log.h"
#include "ais/IAEnemigo.h"

class EntidadEnemigo : public Entidad {
public:
	virtual struct EstadoEnemigo state() = 0;
	virtual float getVelocidadX() = 0;
	virtual void setPosicion(Vector nuevaPosicion) = 0;
	// !!!!!
	virtual void innerTick() = 0;

protected:
	IAEnemigo* ia;
};



#endif //CUCURUCHO_ENTIDADENEMIGO_H
