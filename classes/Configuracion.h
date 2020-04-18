//
// Created by lorenzo on 4/18/20.
//

#ifndef CUCURUCHO_CONFIGURACION_H
#define CUCURUCHO_CONFIGURACION_H

#include <string>

class Configuracion {
public:
    Configuracion(int altoPantalla, int anchoPantalla, int escalaPantalla, int enemigosTipoUno,
            int enemigosTipoDos, std::string nivelLog);

    int getAltoPantalla();
    int getAnchoPantalla();
    int getEscalaPantalla();
    int getEnemigosTipoUno();
    int getEnemigosTipoDos();
    std::string getNivelLog();

private:
    int altoPantalla;
    int anchoPantalla;
    int escalaPantalla;
    int enemigosTipoUno;
    int enemigosTipoDos;
    std::string nivelLog;
};

#endif //CUCURUCHO_CONFIGURACION_H
