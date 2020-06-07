#include <cstring>
#include "Partida.h"
#include "../../../commons/protocols/protocolo.h"
#include "../../../commons/utils/Log.h"
#include "../../../classes/config/FondoConfiguracion.h"


Partida::Partida(Configuracion* config) {
	int anchoPantalla = config->getAnchoPantalla();
	int altoPantalla = config->getAltoPantalla();
	Partida::nuevoNivel = 1;

	for (int i = 0; i < config->getCantidadJugadores(); i++) {
		Partida::jugadores.insert({i, new Jugador(anchoPantalla / 8 * (i + 1), altoPantalla / 2)});
	}

	// !!!! borrar
	/*
    Partida::jugadores.insert({0, new Jugador(anchoPantalla / 8, altoPantalla / 2)});
    Partida::jugadores.insert({1, new Jugador(anchoPantalla / 8 * 2, altoPantalla / 2)});
    Partida::jugadores.insert({2, new Jugador(anchoPantalla / 8 * 3, altoPantalla / 2)});
    Partida::jugadores.insert({3, new Jugador(anchoPantalla / 8 * 4, altoPantalla / 2)});
    */

	Partida::managerNiveles = new ManagerNiveles(config, jugadores);

}

void Partida::tick(struct Comando comandos[]) {
	Partida::nuevoNivel = 1;

	for (int i = 0; i < jugadores.size(); i++) {
		struct Comando comando = comandos[i];
		// !!!! l->error("!!!!" + std::to_string(comando.arriba) + " - " +std::to_string(comando.abajo) + " - " +std::to_string(comando.izquierda) + " - " +std::to_string(comando.derecha) + " - ");
		jugadores.at(i)->calcularVectorVelocidad(comando.arriba,
												 comando.abajo,
												 comando.izquierda,
												 comando.derecha);
	}
    //Render texture to screen
    managerNiveles->tick();
    nuevoNivel = managerNiveles->terminoNivelActual();
}

EstadoInternoNivel Partida::state(struct InformacionNivel* informacionNivel) {
	EstadoInternoNivel estadoInternoNivel;
	estadoInternoNivel.nuevoNivel = nuevoNivel;
    estadoInternoNivel.estadoCampoMovil = managerNiveles->state(informacionNivel);

	if (estadoInternoNivel.nuevoNivel) {
		l->debug("El estado del nivel es distinto de cero:" + std::to_string(estadoInternoNivel.nuevoNivel));
	}

	return estadoInternoNivel;
}
