//
// Created by javier on 29/5/20.
//

#ifndef CUCURUCHO_MANAGERVISTA_H
#define CUCURUCHO_MANAGERVISTA_H

#include <list>
#include "elements/JugadorVista.h"
#include "HudVista.h"
#include "CampoVista.h"
#include "elements/Enemigo1Vista.h"
#include "elements/Enemigo2Vista.h"
#include "elements/DisparoJugadorVista.h"
#include "elements/DisparoEnemigoVista.h"
#include "elements/EnemigoFinal1Vista.h"
#include "elements/ExplosionVista.h"
#include "NivelIntermedioVista.h"
#include "elements/EnemigoFinal1ExtVista.h"

class ManagerVista {
public:
    ManagerVista(struct InformacionNivel, int nivelActual, int ancho, int alto);
    void render(EstadoTick estadoTick, EstadoLogin estadoLogin, std::string username);

    void setInformacionNivel(InformacionNivel informacionNivel, EstadoTick tick);

	void renderNivelIntermedio(EstadoTick estadoTick, EstadoLogin estadoLogin, std::string username);


    void mutear();

private:
    struct InformacionNivel informacionNivel;
    HudVista* hud;
    CampoVista* campoVista;
	Enemigo1Vista* enemigo1Vista;
    Enemigo2Vista* enemigo2Vista;
	EnemigoFinal1Vista* enemigoFinal1Vista;
	DisparoJugadorVista* disparoJugadorVista;
	DisparoEnemigoVista* disparoEnemigoVista;
	NivelIntermedioVista* nivelIntermedioVista;
    std::vector<JugadorVista*>* jugadores = new std::vector<JugadorVista*>();
    std::list<ExplosionVista*> explosiones;

    int nivelActual;
    bool primerNivel;
    int alto;
    int ancho;
    float velocidadNivel;
    Audio* audio;

    void renderEnemigos(std::list<EstadoEnemigo> pEnemigo);

    void renderJugadores(EstadoTick estadoTick, EstadoLogin estadoLogin);

    void renderDisparos(std::list<EstadoDisparo> estadosDisparos);

	void renderDisparosEnemigos(std::list<EstadoDisparo> disparosEnemigos);

	void agregarExplosiones(std::list<EstadoEnemigo> enemigos, std::list<EstadoDisparo> disparosJugador,
							std::list<EstadoDisparo> disparosEnemigo, EstadoJugador estadoJugadores[MAX_JUGADORES]);

    void renderExplosiones();

	void renderHud(EstadoTick estadoTick, EstadoLogin estadoLogin, std::string username);

};


#endif //CUCURUCHO_MANAGERVISTA_H
