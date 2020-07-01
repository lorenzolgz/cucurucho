//
// Created by lorenzo on 4/18/20.
//

#include "Configuracion.h"
#include "UsuariosConfiguracion.h"
#include <list>

Configuracion::Configuracion(int altoPantalla, int anchoPantalla, int escalaPantalla, std::string nivelLog,
                             std::list<NivelConfiguracion *> niveles, int cantidadJugadores, bool std_out,
                             int maxColaEmisora, int maxColaReceptora, UsuariosConfiguracion *usuariosConfiguracion) {
    this->altoPantalla = altoPantalla;
    this->anchoPantalla = anchoPantalla;
    this->escalaPantalla = escalaPantalla;
    this->nivelLog = nivelLog;
    this->niveles = niveles;
    this->cantidadJugadores = cantidadJugadores;
    this->maxColaEmisora = maxColaEmisora;
    this->maxColaReceptora = maxColaReceptora;
    this->std_out = std_out;
    this->usuarios = usuariosConfiguracion;
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

bool Configuracion::isStdOut() const {
    return std_out;
}

int Configuracion::getMaxColaEmisora() const {
    return maxColaEmisora;
}

int Configuracion::getMaxColaReceptora() const {
    return maxColaReceptora;
}

UsuariosConfiguracion *Configuracion::getUsuarios() const {
    return usuarios;
}
