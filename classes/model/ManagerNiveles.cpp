//
// Created by camix on 2/5/20.
//

#include "ManagerNiveles.h"
#include "../view/FondoVista.h"
#include "Hud.h"
#include "../../server/classes/model/ManagerNiveles.h"


ManagerNiveles::ManagerNiveles(Configuracion* config, Jugador* jug) {
    ancho = config->getAnchoPantalla();
    alto = config->getAltoPantalla();
    jugador = jug;
    ManagerNiveles::listNiveles = config->getNiveles();
}

Nivel* ManagerNiveles::configurarNuevoNivel(struct InformacionFondo* informacionFondo) {
	NivelConfiguracion *nivelConfActual = listNiveles.front();
	Nivel *nivel = new Nivel(nivelConfActual, jugador, informacionFondo);
	nivel->crearEnemigos(nivelConfActual->getEnemigos()->getEnemigosClase1(),
						 nivelConfActual->getEnemigos()->getEnemigosClase2());

	l->info("Nuevo nivel creado");
    ManagerNiveles::nivelActual = nivel;
	return nivel;
}

void ManagerNiveles::tick() {
	nivelActual->tick();
}

bool ManagerNiveles::pasajeDeNivel(struct InformacionNivel* informacionNivel){
//  NivelConfiguracion* nivel = listNiveles.front();
    NivelIntermedio* nivelIntermedio = new NivelIntermedio(ancho, alto, HUD_ALTO, informacionNivel->informacionFinNivel);
    nivelIntermedio->tick();
    l->info("Transicion de niveles");

    nivelActual = configurarNuevoNivel(informacionNivel->informacionFondo);
    listNiveles.pop_front();
    return listNiveles.empty();
}

void ManagerNiveles::setEstado(std::list<EstadoEnemigo> estadosEnemigos) {
	nivelActual->setEstado(estadosEnemigos);
}
