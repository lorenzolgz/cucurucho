#include <cstring>
#include "Partida.h"
#include "../../../commons/protocols/protocolo.h"
#include "../../../commons/utils/Log.h"
#include "../../../classes/config/FondoConfiguracion.h"


Partida::Partida(Configuracion* config) {
	int anchoPantalla = config->getAnchoPantalla();
	int altoPantalla = config->getAltoPantalla();

	Partida::nuevoNivel = 1;
	Partida::jugador = new Jugador(anchoPantalla / 8, altoPantalla / 2);
	Partida::managerNiveles = new ManagerNiveles(config, jugador);

}

void Partida::tick(struct Comando command) {

	jugador->calcularVectorVelocidad(command.arriba,
									 command.abajo,
									 command.izquierda,
									 command.derecha);


	//Render texture to screen
	managerNiveles->tick();
	nuevoNivel = managerNiveles->terminoNivelActual();
}

EstadoInternoNivel Partida::state() {
	EstadoInternoNivel estadoInternoNivel;
	estadoInternoNivel.nuevoNivel = nuevoNivel;
	estadoInternoNivel.estadoCampoMovil = managerNiveles->state();

	if (estadoInternoNivel.nuevoNivel) {
		l->debug("El estado del nivel es distinto de cero:" + std::to_string(estadoInternoNivel.nuevoNivel));
	}

	return estadoInternoNivel;
}


void Partida::setNextNivel(InformacionNivel *informacionNivel) {

    NivelConfiguracion* nivelConfig = managerNiveles->setNextNivel();
    if ( nivelConfig == nullptr ) return;
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
    nivelConfig->getFinalNivel(informacionNivel->informacionFinNivel);
//    nuevoNivel = managerNiveles->pasajeDeNivel();
}

bool Partida::terminoNivelActual(){
    return managerNiveles->terminoNivelActual();
}

bool Partida::pasajeDeNivel() {
    return managerNiveles->pasajeDeNivel();
}

bool Partida::estadoJuego() {
    return managerNiveles->estadoJuego();
}
