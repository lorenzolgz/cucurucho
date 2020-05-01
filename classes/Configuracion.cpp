//
// Created by lorenzo on 4/18/20.
//

#include "Configuracion.h"

Configuracion::Configuracion(int altoPantalla, int anchoPantalla, int escalaPantalla, std::map<int, std::queue <int>> enemigos,
        std::string nivelLog, Json::Value recursosNiveles){
    this->altoPantalla = altoPantalla;
    this->anchoPantalla = anchoPantalla;
    this->escalaPantalla = escalaPantalla;
    this->enemigos = enemigos;
    this->nivelLog = nivelLog;
    this->recursosNiveles = recursosNiveles;
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

std::queue <int> Configuracion::getEnemigosNivel(int nivel){
    return this->enemigos.at(nivel);
}

std::string Configuracion::getNivelLog() {
    return this->nivelLog;
}

Json::Value Configuracion::getRecursos(std::string nivel) {
    return this->recursosNiveles[nivel];
}
