#include <cstring>
#include "Partida.h"
#include "../../../commons/protocols/protocolo.h"
#include "../../../commons/utils/Log.h"
#include "../config/FondoConfiguracion.h"


Partida::Partida(Configuracion* config) {
	int anchoPantalla = config->getAnchoPantalla();
	int altoPantalla = config->getAltoPantalla();
	Partida::nuevoNivel = 1;
	Partida::nivel = 1;

    //"jugadores" posee los jugadores que estarán en juego
	for (int i = 0; i < config->getCantidadJugadores(); i++) {
		Partida::jugadores.insert({i, new Jugador(anchoPantalla / 8 * (i + 1), altoPantalla / 2)});
	}

	Partida::managerNiveles = new ManagerNiveles(config, jugadores);
}

void Partida::tick(struct Comando comandos[]) {

	for (int i = 0; i < jugadores.size(); i++) {
		struct Comando comando = comandos[i];

		jugadores.at(i)->calcularVectorVelocidad(comando.arriba,
												 comando.abajo,
												 comando.izquierda,
												 comando.derecha);
	}
    //Render texture to screen
    managerNiveles->tick();
    nuevoNivel = managerNiveles->terminoNivelActual();
    if (nuevoNivel) nivel++;
}

EstadoInternoNivel Partida::state(struct InformacionNivel* informacionNivel) {
	EstadoInternoNivel estadoInternoNivel;
	estadoInternoNivel.nuevoNivel = nuevoNivel;
	estadoInternoNivel.nivel = nivel;
    estadoInternoNivel.estadoCampoMovil = managerNiveles->state(informacionNivel);

	if (estadoInternoNivel.nuevoNivel) {
		l->debug("El estado del nivel es distinto de cero:" + std::to_string(estadoInternoNivel.nuevoNivel));
	}

	return estadoInternoNivel;
}

bool Partida::termino() {
	return managerNiveles->noHayMasNiveles();
}
