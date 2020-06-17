#include <string>

//
// Created by camix on 17/6/20.
//

#ifndef CUCURUCHO_CONFIGURACION_H
#define CUCURUCHO_CONFIGURACION_H


class Configuracion {
public:
    Configuracion(std::string nivelLog);

    std::string getNivelLog();

private:
    std::string nivelLog;
};


#endif //CUCURUCHO_CONFIGURACION_H
