//
// Created by lorenzo on 4/18/20.
//

#ifndef CUCURUCHO_CONFIGURACION_H
#define CUCURUCHO_CONFIGURACION_H

#include <string>
#include <jsoncpp/json/json.h>

class Configuracion {
public:
    Configuracion(int altoPantalla, int anchoPantalla, int escalaPantalla, int enemigosTipoUno,
            int enemigosTipoDos, std::string nivelLog, Json::Value recursosNiveles);

    int getAltoPantalla();
    int getAnchoPantalla();
    int getEscalaPantalla();
    int getEnemigosTipoUno();
    int getEnemigosTipoDos();
    std::string getNivelLog();
    Json::Value getRecursos(std::string nivel);

private:
    int altoPantalla;
    int anchoPantalla;
    int escalaPantalla;
    int enemigosTipoUno;
    int enemigosTipoDos;
    std::string nivelLog;
    Json::Value recursosNiveles;
};

#endif //CUCURUCHO_CONFIGURACION_H
