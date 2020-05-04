//
// Created by camix on 2/5/20.
//

#include "ManagerNiveles.h"
#include "../view/FondoVista.h"
#include "Hud.h"

ManagerNiveles::ManagerNiveles(Configuracion* config, Jugador* jug) {
    ancho = config->getAnchoPantalla();
    alto = config->getAltoPantalla();
    jugador = jug;

    ManagerNiveles::velocidad = VELOCIDAD_INICIAL;
    ManagerNiveles::listNiveles = config->getNiveles();
    ManagerNiveles::nivelActual = configurarNuevoNivel();
}



Nivel* ManagerNiveles::configurarNuevoNivel() {
	NivelConfiguracion *nivelConfActual = listNiveles.front();
	jugador->setPosicion(ancho, alto);
	Nivel *nivel = new Nivel(nivelConfActual, jugador, 1600, alto, velocidad);
	nivel->crearEnemigos(nivelConfActual->getEnemigos()->getEnemigosClase1(),
						 nivelConfActual->getEnemigos()->getEnemigosClase2());

	l.info("Nuevo nivel creado");
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

    CampoMovil* final =  new CampoMovil(nullptr, 960, 672, 96,2);
    final->nuevoFondo(nivel->getFinalNivel() ,0,0,0);
    final->tick();
    l.info("Transicion de niveles");

    listNiveles.pop_front();
    if (listNiveles.empty()) return true;
    ManagerNiveles::velocidad *= AUMENTO_VELOCIDAD_POR_NIVEL;
    nivelActual = configurarNuevoNivel();
    return false;
}


