//
// Created by javier on 29/5/20.
//

#ifndef CUCURUCHO_MANAGERVISTA_H
#define CUCURUCHO_MANAGERVISTA_H

#include <list>
#include "JugadorVista.h"
#include "HudVista.h"
#include "CampoVista.h"
#include "Enemigo1Vista.h"
#include "Enemigo2Vista.h"
#include "DisparoJugadorVista.h"
#include "EnemigoFinal1Vista.h"
#include "ExplosionVista.h"

class ManagerVista {
public:
    ManagerVista(struct InformacionNivel, int nivelActual, int ancho, int alto);
    void render(EstadoTick estadoTick, EstadoLogin estadoLogin, std::string username);

    void renderNivelIntermedio();

    void setInformacionNivel(InformacionNivel informacionNivel, EstadoTick tick);

private:
    struct InformacionNivel informacionNivel;
    HudVista* hud;
    CampoVista* campoVista;
	Enemigo1Vista* enemigo1Vista;
    Enemigo2Vista* enemigo2Vista;
	EnemigoFinal1Vista* enemigoFinal1Vista;
    DisparoJugadorVista disparoJugadorVista;
    std::vector<JugadorVista*>* jugadores = new std::vector<JugadorVista*>();
    std::list<ExplosionVista*> explosiones;

    int nivelActual;
    bool primerNivel;
    int alto;
    int ancho;
    float velocidadNivel;

    void renderEnemigos(std::list<EstadoEnemigo> pEnemigo);

    void renderJugadores(EstadoTick estadoTick, EstadoLogin estadoLogin);

    void renderEsperaJugador(JugadorVista* jugador, char* nombre, int indice, int colorTexto, int cantJugadores);

    void renderEspera(struct EstadoLogin estadoLogin);

    void renderDisparos(std::list<EstadoDisparo> estadosDisparos);

    void renderExplosiones(std::list<EstadoEnemigo> list);
};


#endif //CUCURUCHO_MANAGERVISTA_H
