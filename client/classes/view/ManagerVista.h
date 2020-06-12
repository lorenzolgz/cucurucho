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
#include "Enemigo1Vista.h"
#include "Enemigo2Vista.h"

class ManagerVista {
public:
    ManagerVista(struct InformacionNivel, int nivelActual, int ancho, int alto);
    void render(EstadoTick estadoTick, EstadoLogin estadoLogin);

    void renderNivelIntermedio();

    void setInformacionNivel(InformacionNivel informacionNivel);

private:
    struct InformacionNivel informacionNivel;
    HudVista hud;
    CampoVista* campoVista;
    Enemigo1Vista enemigo1Vista;
    Enemigo2Vista enemigo2Vista;
    std::vector<JugadorVista*> jugadores;
    int nivelActual;
    int alto;
    int ancho;
    float posX;

    void renderEnemigos(EstadoEnemigo pEnemigo[15]);

    void renderEsperaJugador(JugadorVista* jugador, char* nombre, int indice, int colorTexto);

    void renderEspera(struct EstadoLogin estadoLogin);
};


#endif //CUCURUCHO_MANAGERVISTA_H
