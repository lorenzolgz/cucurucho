//
// Created by lorenzo on 4/18/20.
//

#include "Configuracion.h"

Configuracion::Configuracion(int altoPantalla, int anchoPantalla, int escalaPantalla, int enemigosTipoUno, int enemigosTipoDos,
        std::string nivelLog, Json::Value recursosNiveles) {
    this->altoPantalla = altoPantalla;
    this->anchoPantalla = anchoPantalla;
    this->escalaPantalla = escalaPantalla;
    this->enemigosTipoUno = enemigosTipoUno;
    this->enemigosTipoDos = enemigosTipoDos;
    this->nivelLog = nivelLog;
    this->recursosNiveles = recursosNiveles;
};

int Configuracion::getAltoPantalla(){
    return this->altoPantalla;
}

int Configuracion::getAnchoPantalla(){
    return this->anchoPantalla;
}

int Configuracion::getEscalaPantalla(){
    return this->escalaPantalla;
}

int Configuracion::getEnemigosTipoUno(){
    return this->enemigosTipoUno;
}

int Configuracion::getEnemigosTipoDos(){
    return this->enemigosTipoDos;
}

std::string Configuracion::getNivelLog() {
    return this->nivelLog;
}

Json::Value Configuracion::getRecursos(std::string nivel) {
    return this->recursosNiveles[nivel];
}