//
// Created by camix on 2/6/20.
//

#include "FondoConfiguracion.h"
#include "../../classes/config/FondoConfiguracion.h"


#include <utility>
#include <iostream>
#include <cstring>

FondoConfiguracion::FondoConfiguracion(const char* archivo, double velocidad) :
                                                                                       velocidad(velocidad) {
    strcpy(arch, archivo);
}

double FondoConfiguracion::getVelocidad() const {
    return velocidad;
}

void FondoConfiguracion::setArchivo(char *archivo) const {
    strcpy(archivo, arch);
}

const char *FondoConfiguracion::getArchivo() const {
    return arch;
}
