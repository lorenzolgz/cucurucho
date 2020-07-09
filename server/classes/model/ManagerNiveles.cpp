//
// Created by camix on 2/5/20.
//

#include "ManagerNiveles.h"
#include "../../../commons/utils/Log.h"

ManagerNiveles::ManagerNiveles(Configuracion* config, std::map<int, Jugador*> jugadores) {
    ancho = config->getAnchoPantalla();
    alto = config->getAltoPantalla();
    ManagerNiveles::jugadores = jugadores;

    ManagerNiveles::nivelesConfiguracion = config->getNiveles();
    ManagerNiveles::nivelActual = configurarNuevoNivel();
	ManagerNiveles::nuevoNivel = 1;
	ManagerNiveles::cantidadNivelesTerminados = 0;
	ManagerNiveles::totalNiveles = nivelesConfiguracion.size();
}

Nivel* ManagerNiveles::configurarNuevoNivel() {
	NivelConfiguracion *nivelConfActual = nivelesConfiguracion.front();

    std::map<int, Jugador*>::iterator it;
    int pos = 1;
    for (it = jugadores.begin(); it != jugadores.end(); it++) {
        it->second->resetState();
        // TODO sacar esto y que el server sea agnostico al HUD
		const int HUD_ALTO = 96;
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

    if (nuevoNivel) {
    	cantidadNivelesTerminados = cantidadNivelesTerminados +	 1;
    }

    return nuevoNivel;
}

void ManagerNiveles::pasajeDeNivel(){
    l->info("Transicion de niveles");

    nivelActual = configurarNuevoNivel();
    nivelesConfiguracion.pop_front();
}

EstadoInternoCampoMovil ManagerNiveles::state(struct InformacionNivel* informacionNivel) {
	if (nuevoNivel) {
		informacionNivel->numeroNivel++;
		NivelConfiguracion *nivelConfig = nivelesConfiguracion.front();
		if (nivelConfig == nullptr) return nivelActual->state();

        std::list<InformacionFondo> listaFondo;
		for (FondoConfiguracion *f : nivelConfig->getFondos()) {
			InformacionFondo info;
		    info.pVelocidad = f->getVelocidad();
		    f->setArchivo(info.pFondo);
		    listaFondo.push_back(info);
		}
        informacionNivel->informacionFondo = listaFondo;
        informacionNivel->velocidad = nivelConfig->getVelocidad();
		nivelConfig->getFinalNivel(informacionNivel->informacionFinNivel);
		pasajeDeNivel();
	}
    return nivelActual->state();
}

bool ManagerNiveles::noHayMasNiveles() {
	return cantidadNivelesTerminados == totalNiveles;
}

bool ManagerNiveles::nuevoDisparo(Disparo *disparo) {
    return this->nivelActual->nuevoDisparo(disparo);
}

