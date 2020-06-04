//
// Created by camix on 2/5/20.
//

#include "ManagerNiveles.h"
#include "Hud.h"
#include "../../../commons/utils/Log.h"

ManagerNiveles::ManagerNiveles(Configuracion* config, std::map<int, Jugador*> jugadores) {
    ancho = config->getAnchoPantalla();
    alto = config->getAltoPantalla();
    ManagerNiveles::jugadores = jugadores;

    ManagerNiveles::listNiveles = config->getNiveles();
    ManagerNiveles::nivelActual = configurarNuevoNivel();
}


Nivel* ManagerNiveles::configurarNuevoNivel() {
	NivelConfiguracion *nivelConfActual = listNiveles.front();



    std::map<int, Jugador*>::iterator it;
    int pos = 1;
    for (it = jugadores.begin(); it != jugadores.end(); it++) {
        it->second->setPosicion(ancho / 8 * pos, alto / 2 - HUD_ALTO);
        pos++;
    }
	Nivel *nivel = new Nivel(nivelConfActual, jugadores);
	nivel->crearEnemigos(nivelConfActual->getEnemigos()->getEnemigosClase1(),
						 nivelConfActual->getEnemigos()->getEnemigosClase2());

	l->info("Nuevo nivel creado");
	return nivel;
}

void ManagerNiveles::tick() {
	nivelActual->tick();
}

bool ManagerNiveles::terminoNivelActual() {
    return nivelActual->termino();
}

bool ManagerNiveles::estadoJuego() {
	return listNiveles.empty();
}

bool ManagerNiveles::pasajeDeNivel(){
    NivelConfiguracion* nivel = listNiveles.front();

    NivelIntermedio* nivelIntermedio = new NivelIntermedio(ancho, alto, HUD_ALTO, nivel->getFinalNivel());
    nivelIntermedio->tick();
    l->info("Transicion de niveles");

    listNiveles.pop_front();
    if (listNiveles.empty()) return true;
    nivelActual = configurarNuevoNivel();
    return false;
}

EstadoInternoCampoMovil ManagerNiveles::state() {
	return nivelActual->state();
}
