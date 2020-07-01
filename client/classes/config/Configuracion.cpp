//
// Created by camix on 17/6/20.
//

#include "Configuracion.h"


Configuracion::Configuracion(std::string nivelLog, bool std_out, int maxCola) {
    this->nivelLog = nivelLog;
    this->std_out = std_out;
    this->maxCola = maxCola;
}

int Configuracion::getMaxCola() const {
    return maxCola;
}

bool Configuracion::isStdOut() const {
    return std_out;
}


std::string Configuracion::getNivelLog() {
    return this->nivelLog;
}

