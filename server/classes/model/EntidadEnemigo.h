#ifndef CUCURUCHO_ENTIDADENEMIGO_H
#define CUCURUCHO_ENTIDADENEMIGO_H


#include "entities/Entidad.h"
#include "Jugador.h"
#include "../../../commons/utils/Log.h"

class EntidadEnemigo : public Entidad {
public:
	virtual struct EstadoEnemigo state() = 0;
    virtual void aproximarAJugador(std::map<int, Jugador *> jugadores){l->debug("No se realiza IA de aproximacion porque no implementada");}
};



#endif //CUCURUCHO_ENTIDADENEMIGO_H
