//
// Created by camix on 17/6/20.
//

#ifndef CUCURUCHO_CONFIGURACION_H
#define CUCURUCHO_CONFIGURACION_H


#include <string>

class Configuracion {
public:
    Configuracion(std::string nivelLog, bool b, int i, bool invencible);

    std::string getNivelLog();
    bool isStdOut() const;
    int getMaxCola() const;
	bool isInvencible() const;

private:
    std::string nivelLog;
    bool std_out;
    int maxCola;
    bool invencible;
};


#endif //CUCURUCHO_CONFIGURACION_H
