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
#include "../../../commons/utils/Constantes.h"
#include "Disparo.h"

#define VELOCIDAD_INICIAL 2
#define AUMENTO_VELOCIDAD_POR_NIVEL 1.1

class ManagerNiveles : public Ticker {
public:
    ManagerNiveles(Configuracion* config, std::map<int, Jugador*> jugadores);

    void tick() override;
    void pasajeDeNivel();
	bool terminoNivelActual();
	EstadoInternoCampoMovil state(struct InformacionNivel* informacionNivel);
    Nivel *configurarNuevoNivel();
    bool noHayMasNiveles();
    bool nuevoDisparo(Disparo* disparo);

private:
    std::list<NivelConfiguracion *> nivelesConfiguracion;
    Nivel* nivelActual;
    int alto;
    int ancho;
    std::map<int, Jugador*> jugadores;
    int nuevoNivel;
    int cantidadNivelesTerminados;
    int totalNiveles;
};


#endif //CUCURUCHO_MANAGERNIVELES_H
