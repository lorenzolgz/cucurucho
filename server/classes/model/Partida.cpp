#include "Partida.h"
#include "../../../commons/protocols/protocolo.h"
#include "../../../commons/utils/Log.h"


Partida::Partida(Configuracion* config) {
	int anchoPantalla = config->getAnchoPantalla();
	int altoPantalla = config->getAltoPantalla();

	Partida::nuevoNivel = 0;
	Partida::jugador = new Jugador(anchoPantalla / 8, altoPantalla / 2);
	Partida::managerNiveles = new ManagerNiveles(config, jugador);

}

void Partida::tick(struct Comando command) {
	if (nuevoNivel > 0) {
		nuevoNivel = managerNiveles->pasajeDeNivel();
	}

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
