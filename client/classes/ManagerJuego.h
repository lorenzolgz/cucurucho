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

    void nuevoMensaje(nlohmann::json instruccion);

    void render();

    bool terminoJuego();

    bool enJuego();

    void setInformacionNivel(const InformacionNivel &informacionNivel);

    void setEstadoTick(const EstadoTick &estadoTick);

    void setEstadoLogin(const EstadoLogin &estadoLogin);

private:
    InformacionNivel informacionNivel;
    EstadoTick estadoTick;
    ManagerVista* managerVista;
    EstadoLogin estadoLogin;
    Titulo* titulo;

};


#endif //CUCURUCHO_MANAGERJUEGO_H
