#include <cstring>
#include "Partida.h"
#include "../../../commons/protocols/protocolo.h"
#include "../../../commons/utils/Log.h"
#include "../config/FondoConfiguracion.h"

#define ANCHO_DISPARO 10
#define ALTO_DISPARO 10
#define VELOCIDAD_DISPARO 7

Partida::Partida(Configuracion* config) {
	Partida::nuevoNivel = 1;
	Partida::nivel = 1;

    //"jugadores" posee los jugadores que estarán en juego
	for (int i = 0; i < config->getCantidadJugadores(); i++) {
		Partida::jugadores.insert({i, new Jugador(config, i)});
	}

	Partida::managerNiveles = new ManagerNiveles(config, jugadores);
}

void Partida::tick(struct Comando comandos[]) {

	for (int i = 0; i < jugadores.size(); i++) {
		struct Comando comando = comandos[i];
		Jugador *jugadorActual = jugadores.at(i);

		jugadorActual->calcularVectorVelocidad(comando.arriba,
											   comando.abajo,
											   comando.izquierda,
											   comando.derecha);

		if (comandos[i].disparo) {
			Disparo* disparo = jugadorActual->disparar();
			if (disparo == nullptr) {
				l->debug("El jugador " + std::to_string(i) + " no disparó porque está en cooldown");
			} else {
				l->debug("El jugador " + std::to_string(i) + " disparó");
				managerNiveles->nuevoDisparo(disparo);
			}
		}

		jugadorActual->cambiarInvencible(comando.invencible);
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
