#include <cstring>
#include "Partida.h"
#include "../../../commons/protocols/protocolo.h"
#include "../../../commons/utils/Log.h"
#include "../config/FondoConfiguracion.h"

Partida::Partida(Configuracion* config) {
	this->nuevoNivel = 1;
	this->nivel = 1;
	this->jugadores = new std::map<int, Jugador*>();

    //"jugadores" posee los jugadores que estarán en juego
	for (int i = 0; i < config->getCantidadJugadores(); i++) {
		jugadores->insert({i, new Jugador(config, i)});
	}

	this->managerNiveles = new ManagerNiveles(config, jugadores);
}

void Partida::tick(struct Comando comandos[]) {

	for (int i = 0; i < jugadores->size(); i++) {
		struct Comando comando = comandos[i];
		Jugador *jugadorActual = jugadores->at(i);

		jugadorActual->calcularVectorVelocidad(comando.arriba,
											   comando.abajo,
											   comando.izquierda,
											   comando.derecha);

		if (comandos[i].disparo) {
			std::list<Disparo*> disparos = jugadorActual->disparar();
			if (disparos.empty()) {
				l->debug("El jugador " + std::to_string(i) + " no disparó. Puede que este en cooldown o este muerto.");
			} else {
				for (Disparo* disparo : disparos) {
					managerNiveles->nuevoDisparo(disparo);
				}
				l->debug("El jugador " + std::to_string(i) + " disparó");
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
