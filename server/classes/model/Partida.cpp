#include "Partida.h"
#include "../../../commons/protocols/protocolo.h"


Partida::Partida(Configuracion* config) {
	int anchoPantalla = config->getAnchoPantalla();
	int altoPantalla = config->getAltoPantalla();

	Partida::jugador = new Jugador(anchoPantalla / 8, altoPantalla / 2);
	Partida::managerNiveles = new ManagerNiveles(config, jugador);

}

void Partida::tick(struct Comando command) {
	bool terminoNivelActual = false;

	jugador->calcularVectorVelocidad(command.arriba,
									 command.abajo,
									 command.izquierda,
									 command.derecha);


	//Render texture to screen
	managerNiveles->tick();
	terminoNivelActual = managerNiveles->terminoNivelActual();
	if (terminoNivelActual) {
		terminoNivelActual = managerNiveles->pasajeDeNivel();
	}
}

EstadoCampoMovil Partida::state() {
	return managerNiveles->state();
}
