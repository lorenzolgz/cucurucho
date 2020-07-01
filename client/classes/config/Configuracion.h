#include <string>

//
// Created by camix on 17/6/20.
//

#ifndef CUCURUCHO_CONFIGURACION_H
#define CUCURUCHO_CONFIGURACION_H


class Configuracion {
public:
    Configuracion(std::string nivelLog, bool b, int i);

    std::string getNivelLog();

    bool isStdOut() const;

    int getMaxCola() const;


private:
    std::string nivelLog;
    bool std_out;
    int maxCola;
};


#endif //CUCURUCHO_CONFIGURACION_H
