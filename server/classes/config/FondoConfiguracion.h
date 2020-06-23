//
// Created by camix on 2/6/20.
//

#ifndef CUCURUCHO_FONDOCONFIGURACION_H
#define CUCURUCHO_FONDOCONFIGURACION_H

#include <string>

class FondoConfiguracion {
public:
    FondoConfiguracion(const char* archivo, double velocidad);

    const char *getArchivo() const;
    double getVelocidad() const;
    void setArchivo(char *archivo) const;

private:
    char arch[255];
    double velocidad;

};

#endif //CUCURUCHO_FONDOCONFIGURACION_H
