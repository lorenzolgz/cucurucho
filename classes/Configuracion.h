//
// Created by lorenzo on 4/18/20.
//

#ifndef CUCURUCHO_CONFIGURACION_H
#define CUCURUCHO_CONFIGURACION_H

#include <string>
#include <queue>
#include <jsoncpp/json/json.h>

class Configuracion {
public:
    Configuracion(int altoPantalla, int anchoPantalla, int escalaPantalla, std::map<int, std::queue <int>> enemigos,
                    std::string nivelLog, Json::Value recursosNiveles);

    int getAltoPantalla();
    int getAnchoPantalla();
    int getEscalaPantalla();
    std::queue <int> getEnemigosNivel(int nivel);
    std::string getNivelLog();
    Json::Value getRecursos(std::string nivel);

private:
    int altoPantalla;
    int anchoPantalla;
    int escalaPantalla;
    std::map<int, std::queue <int>> enemigos;
    std::string nivelLog;
    Json::Value recursosNiveles;
};

#endif //CUCURUCHO_CONFIGURACION_H
