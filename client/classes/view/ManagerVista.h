//
// Created by javier on 29/5/20.
//

#ifndef CUCURUCHO_MANAGERVISTA_H
#define CUCURUCHO_MANAGERVISTA_H


#include <list>
#include "JugadorVista.h"
#include "../config/NivelConfiguracion.h"
#include "HudVista.h"
#include "CampoVista.h"

class ManagerVista {
public:
    ManagerVista(JugadorVista* jugador, std::vector<NivelConfiguracion*> listNiveles, int nivelActual, int ancho, int alto);
    void render();
    void cambiarNivel(int nivel);

private:
    JugadorVista* jugador;
    std::vector<NivelConfiguracion *> listNiveles;
    HudVista hud;
    CampoVista* campoVista;
    int nivelActual;
    int alto;
    int ancho;
    float posX;
};


#endif //CUCURUCHO_MANAGERVISTA_H
