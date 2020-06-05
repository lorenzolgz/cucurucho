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

EstadoInternoNivel Partida::state(struct InformacionNivel* informacionNivel) {
	EstadoInternoNivel estadoInternoNivel;
	estadoInternoNivel.nuevoNivel = nuevoNivel;
	estadoInternoNivel.estadoCampoMovil = managerNiveles->state(informacionNivel);
	return estadoInternoNivel;
}


bool Partida::estadoJuego() {
    return managerNiveles->estadoJuego();
}
