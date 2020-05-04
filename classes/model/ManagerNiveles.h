//
// Created by camix on 2/5/20.
//

#ifndef CUCURUCHO_MANAGERNIVELES_H
#define CUCURUCHO_MANAGERNIVELES_H


#include <jsoncpp/json/value.h>
#include <chrono>
#include <thread>
#include "../config/Configuracion.h"
#include "CampoMovil.h"
#include "Nivel.h"

#define VELOCIDAD_INICIAL 2
#define AUMENTO_VELOCIDAD_POR_NIVEL 1.1

class ManagerNiveles : public Ticker {
public:
    ManagerNiveles(Configuracion* config, Jugador* jugador);

    void tick() override;
    bool estadoJuego();
    bool pasajeDeNivel();
	bool terminoNivelActual();

private:
    std::list<NivelConfiguracion *> listNiveles;
    Nivel* nivelActual;
    int velocidad;
    int alto;
    int ancho;
    Jugador* jugador;

    Nivel *configurarNuevoNivel();

};


#endif //CUCURUCHO_MANAGERNIVELES_H