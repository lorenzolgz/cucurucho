//
// Created by camix on 17/6/20.
//

#include "Configuracion.h"
#include "../../../commons/utils/Log.h"

Configuracion::Configuracion(std::string nivelLog, bool std_out, int maxCola, bool invencible) {
    this->nivelLog = nivelLog;
    this->std_out = std_out;
    this->maxCola = maxCola;
    this->invencible = invencible;
    l->error("!!!!! Invencible: " + std::to_string(this->invencible));
}

int Configuracion::getMaxCola() const {
    return maxCola;
}

bool Configuracion::isInvencible() const {
	return invencible;
}

bool Configuracion::isStdOut() const {
    return std_out;
}

std::string Configuracion::getNivelLog() {
    return this->nivelLog;
}
