//
// Created by lorenzo on 4/18/20.
//

#include "Configuracion.h"
#include <list>

Configuracion::Configuracion(int altoPantalla, int anchoPantalla, int escalaPantalla, std::string nivelLog,
		std::list<NivelConfiguracion*> niveles, int cantidadJugadores){
    this->altoPantalla = altoPantalla;
    this->anchoPantalla = anchoPantalla;
    this->escalaPantalla = escalaPantalla;
    this->nivelLog = nivelLog;
    this->niveles = niveles;
    this->cantidadJugadores = cantidadJugadores;
}

int Configuracion::getAltoPantalla(){
    return this->altoPantalla;
}

int Configuracion::getAnchoPantalla(){
    return this->anchoPantalla;
}

int Configuracion::getEscalaPantalla(){
    return this->escalaPantalla;
}

std::string Configuracion::getNivelLog() {
    return this->nivelLog;
}

int Configuracion::getCantidadJugadores() {
    return this->cantidadJugadores;
}

const std::list<NivelConfiguracion *> &Configuracion::getNiveles() const {
	return niveles;
}
