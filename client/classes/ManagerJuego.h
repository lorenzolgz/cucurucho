//
// Created by camix on 10/6/20.
//

#ifndef CUCURUCHO_MANAGERJUEGO_H
#define CUCURUCHO_MANAGERJUEGO_H


#include "../../libraries/json/json.hpp"
#include "view/ManagerVista.h"
#include "view/Titulo.h"

class ManagerJuego {
public:
    ManagerJuego();

    void estadoNivel(nlohmann::json instruccion);

    void render();

    bool terminoJuego();

private:
    InformacionNivel informacionNivel;
    EstadoTick estadoTick;
    ManagerVista *managerVista;

    void setEstadoTick(nlohmann::json mensaje);
    void setInformacionNivel(nlohmann::json mensaje);

};


#endif //CUCURUCHO_MANAGERJUEGO_H
