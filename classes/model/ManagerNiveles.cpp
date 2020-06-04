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


bool ManagerNiveles::estadoJuego() {
	return listNiveles.empty();
}

bool ManagerNiveles::pasajeDeNivel(struct InformacionNivel* informacionNivel){
    NivelConfiguracion* nivel = listNiveles.front();
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

//void ManagerNiveles::setFondo(struct InformacionFondo* informacionFondo) {
//    // tomar los fondos que se pasan por parametro en vez de tomar los del backup
//}

void ManagerNiveles::setNivelIntermedio(char* archivo){
    NivelIntermedio* nivelIntermedio = new NivelIntermedio(ancho, alto, HUD_ALTO, archivo);
    nivelIntermedio->tick();
    l->info("Transicion de niveles");
}
