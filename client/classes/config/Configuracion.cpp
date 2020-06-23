//
// Created by camix on 17/6/20.
//

#include "Configuracion.h"


Configuracion::Configuracion(std::string nivelLog){
    this->nivelLog = nivelLog;
}


std::string Configuracion::getNivelLog() {
    return this->nivelLog;
}
