#ifndef CUCURUCHO_MANAGERNIVELES_H
#define CUCURUCHO_MANAGERNIVELES_H


#include <jsoncpp/json/value.h>
#include <chrono>
#include <thread>
#include "../config/Configuracion.h"
#include "CampoMovil.h"
#include "Nivel.h"
#include "NivelIntermedio.h"
#include "../states/EstadoInternoNivel.h"

#define VELOCIDAD_INICIAL 2
#define AUMENTO_VELOCIDAD_POR_NIVEL 1.1

class ManagerNiveles : public Ticker {
public:
    ManagerNiveles(Configuracion* config, std::map<int, Jugador*> jugadores);

    void tick() override;
    bool estadoJuego();
    bool pasajeDeNivel();
	bool terminoNivelActual();
	EstadoInternoCampoMovil state();

private:
    std::list<NivelConfiguracion *> listNiveles;
    Nivel* nivelActual;
    int alto;
    int ancho;
    std::map<int, Jugador*> jugadores;

    Nivel *configurarNuevoNivel();

};


#endif //CUCURUCHO_MANAGERNIVELES_H