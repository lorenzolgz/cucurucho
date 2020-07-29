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

    void setUsername(const std::string &username);

	void render();

	void renderFinJuego();

    bool terminoJuego();

    bool enJuego();

    void setInformacionNivel(const InformacionNivel &informacionNivel);

    void setEstadoTick(const EstadoTick &estadoTick);

    void setEstadoLogin(const EstadoLogin &estadoLogin);

    void mutear();

private:
    InformacionNivel informacionNivel;
    EstadoTick estadoTick;
    ManagerVista* managerVista;
    EstadoLogin estadoLogin;
    std::string username;

	void verificarJugadoresMuertos(const EstadoTick tick);

	Audio* audio;
    std::string audioPerder;

};


#endif //CUCURUCHO_MANAGERJUEGO_H
