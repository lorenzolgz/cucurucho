#include "HiloOrquestadorPartida.h"
#include "../../commons/utils/Log.h"
#include "HiloConexionServidor.h"
#include "../../commons/ColaBloqueante.h"

void initializeData(struct EstadoTick* estadoTick);
void processData(Partida* partida, struct Comando comandos[], struct EstadoTick* estadoTick, struct InformacionNivel* informacionNivel);
int esperarConexiones(int puerto, Configuracion* config);
Configuracion* parsearConfiguracion();

HiloOrquestadorPartida::HiloOrquestadorPartida(Configuracion *config, std::list<ConexionServidor*> conexiones) {
	this->config = config;
	this->conexiones = conexiones;
	this->partida = new Partida(config);

}

void HiloOrquestadorPartida::run() {
	l->info("Comenzando a correr HiloOrquestadorPartida");
	bool quit = false;
	struct Comando comandos[conexiones.size()];
	struct InformacionNivel informacionNivel;
	struct EstadoTick estadoTick;
	bool terminoNivelActual = false;
	clock_t t2, t1 = clock();

	int commands_count = 0;
	initializeData(&estadoTick);
	informacionNivel.numeroNivel = 0;
	std::list<HiloConexionServidor*> hilosConexionesServidores;
	std::list<ColaBloqueante<nlohmann::json>*> colasReceptoras;

	// Comunicacion inicial.
	int nuevoNivel = 1;

	for (auto* conexion : conexiones) {
		auto* colaReceptora = new ColaBloqueante<nlohmann::json>();
		colasReceptoras.push_back(colaReceptora);
		auto* hiloConexionServidor = new HiloConexionServidor(conexion, colaReceptora);
		hiloConexionServidor->start();
		hilosConexionesServidores.push_back(hiloConexionServidor);
	}

	//keep communicating with client
	try {
		while (!quit) {

			// WIP. Para controlar la cantidad de ticks.
			t2 = clock();
			if ((t2 - t1) > 50) {
				//DO the stuff!
				// printf("!!!! %d\n", t2-t1);
				t1 = clock();
			}

			// Receive data (command)
			int contadorColasReceptoras = 0;
			for (auto* colaReceptora : colasReceptoras) {
				nlohmann::json comandoJson = colaReceptora->pop();
				struct Comando comando = {comandoJson["arriba"], comandoJson["abajo"], comandoJson["izquierda"], comandoJson["derecha"]};
				comandos[contadorColasReceptoras] = comando;
				contadorColasReceptoras++;
			}
			//--------------------

			// Process model
			processData(partida, comandos, &estadoTick, &informacionNivel);
			//--------------------

			if (nuevoNivel) {
				l->debug("Nuevo nivel enviando : " + std::to_string(informacionNivel.numeroNivel));
			}

			// Send data (view)
			if (nuevoNivel) {
				for (auto *conexion : conexiones) {
					conexion->enviarInformacionNivel(&informacionNivel);
				}
				nuevoNivel = false;
			} else {
				for (auto *conexion : conexiones) {
					conexion->enviarEstadoTick(&estadoTick);
				}
				nuevoNivel = estadoTick.nuevoNivel;
			}

			// printf("Send data: pos(X,Y) = (%d,%d)\n\n", client_view.posicionX, client_view.posicionY);
			//--------------------

			commands_count++;
		}
	}
	catch (const std::exception& exc) {
		l->error("HiloOrquestadorPartida. Ocurrio un error en el main loop");
	}

	for (auto* hiloConexionServidor : hilosConexionesServidores) {
		hiloConexionServidor->join();
	}
}

void processData(Partida* partida, struct Comando comandos[], struct EstadoTick* estadoTick, struct InformacionNivel* informacionNivel) {
	EstadoInternoNivel estadoInternoNivel = partida->state(informacionNivel);
	partida->tick(comandos);

	// Seteando estadoTick
	estadoTick->nuevoNivel = estadoInternoNivel.nuevoNivel;
	EstadoInternoCampoMovil estadoCampoMovil = estadoInternoNivel.estadoCampoMovil;
	int i = 0;
	for (EstadoJugador estadoJugador : estadoCampoMovil.estadosJugadores) {
		estadoTick->estadosJugadores[i] = estadoJugador;
		i++;
	}
	i = 0;
	for (EstadoEnemigo estadoEnemigo : estadoCampoMovil.estadosEnemigos) {
		estadoTick->estadosEnemigos[i] = estadoEnemigo;
		i++;
	}
	// !!!! hardcodeadisimo
	for (; i < MAX_ENEMIGOS; i++) {
		estadoTick->estadosEnemigos[i].clase = 0;
	}
}


void initializeData(struct EstadoTick* estadoTick) {
	for (int i = 0; i < MAX_JUGADORES; i++) {
		estadoTick->estadosJugadores[i].posicionX = -1000;
		estadoTick->estadosJugadores[i].posicionY = -1000;
		estadoTick->estadosJugadores[i].helper1.posicionX = -1000;
		estadoTick->estadosJugadores[i].helper1.posicionY = -1000;
		estadoTick->estadosJugadores[i].helper2.posicionX = -1000;
		estadoTick->estadosJugadores[i].helper2.posicionY = -1000;
	}

	for (int i = 0; i < MAX_ENEMIGOS; i++) {
		estadoTick->estadosEnemigos[i].clase = 0;
	}
}