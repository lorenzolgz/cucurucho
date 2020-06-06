//
// Created by camix on 2/5/20.
//

#include <cstring>
#include "ManagerNiveles.h"
#include "Hud.h"
#include "../../../commons/utils/Log.h"
#include "../config/NivelConfiguracion.h"

ManagerNiveles::ManagerNiveles(Configuracion* config, std::map<int, Jugador*> jugadores) {
    ancho = config->getAnchoPantalla();
    alto = config->getAltoPantalla();
    ManagerNiveles::jugadores = jugadores;

    ManagerNiveles::listNiveles = config->getNiveles();
    ManagerNiveles::nivelActual = configurarNuevoNivel();
    ManagerNiveles::nuevoNivel = 1;
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
    nuevoNivel = nivelActual->termino();
    return nuevoNivel;
}

bool ManagerNiveles::estadoJuego() {
	return listNiveles.empty();
}

bool ManagerNiveles::pasajeDeNivel(){
    NivelConfiguracion* nivel = listNiveles.front();

    NivelIntermedio* nivelIntermedio = new NivelIntermedio(ancho, alto, HUD_ALTO, nivel->getFinalNivel());
    nivelIntermedio->tick();
    l->info("Transicion de niveles");

    nivelActual = configurarNuevoNivel();
    listNiveles.pop_front();
    return false;
}

EstadoInternoCampoMovil ManagerNiveles::state(struct InformacionNivel* informacionNivel) {
    if (nuevoNivel){
        informacionNivel->numeroNivel++;
        NivelConfiguracion* nivelConfig = listNiveles.front();
        if ( nivelConfig == nullptr ) return nivelActual->state();
        int i = 0;
        for( FondoConfiguracion* f : nivelConfig->getFondos() ) {
            informacionNivel->informacionFondo[i].pVelocidad = f->getVelocidad();
            f->setArchivo(informacionNivel->informacionFondo[i].pFondo);
            i++;
        }
        for (i; i< MAX_FONDOS; i++){
            informacionNivel->informacionFondo[i].pVelocidad = 0;
            strcpy(&informacionNivel->informacionFondo[i].pFondo[0],"\0");
        }
        informacionNivel->velocidad= nivelConfig->getVelocidad();
        nivelConfig->getFinalNivel(informacionNivel->informacionFinNivel);
        pasajeDeNivel();
    }

	return nivelActual->state();
}

