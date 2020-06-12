#include "HiloOrquestadorPartida.h"
#include "../../commons/utils/Log.h"
#include "HiloConexionServidor.h"
#include "../../commons/ColaBloqueante.h"

void initializeData(struct EstadoTick* estadoTick);
void processData(Partida* partida, struct Comando comandos[], struct EstadoTick* estadoTick, struct InformacionNivel* informacionNivel);
int esperarConexiones(int puerto, Configuracion* config);
Configuracion* parsearConfiguracion();

HiloOrquestadorPartida::HiloOrquestadorPartida(Configuracion *config, std::list<ConexionServidor*>* conexiones) {
	this->config = config;
	this->conexiones = conexiones;
	this->partida = new Partida(config);

}

bool receiveData(std::list<HiloConexionServidor*>* hilosConexionesServidores, struct Comando *comandos) {
	// Esta variable se necesita porque el servidor va mas rapido que los clientes, entonces cuando no hay actividad, que siga de largo.
	bool seRecibioComando = false;

	hilosConexionesServidores->reverse();

	// Uno de los clientes se queda esperando al resto, por eso siempre unos se ven mejor y otros peor.
	for (auto* hiloConexionServidor : *(hilosConexionesServidores)) {
		auto* colaReceptora = hiloConexionServidor->colaReceptora;
		nlohmann::json mensajeJson;

		while (colaReceptora->size() > MAX_COLA_SERVIDOR) {
            colaReceptora->pop();
		}

		// Notar que esto es bloqueante si la cola esta vacia! Se queda esperando a que deje de estarlo.
		mensajeJson = colaReceptora->pop();

		if (mensajeJson["_t"] == COMANDO) {
			seRecibioComando = true;
			struct Comando comando = {mensajeJson["nroJugador"], mensajeJson["arriba"], mensajeJson["abajo"], mensajeJson["izquierda"], mensajeJson["derecha"]};
			comandos[comando.nroJugador-1] = comando;
		} else {
			l->error("HiloOrquestadorPartida. Recibiendo mensaje invalido");
		}
	}

	return seRecibioComando;

	// !!!! Dejo esta linea aca porque es muy buena
	/*
		struct Comando comando = comandos[i];
		if (comando.arriba || comando.abajo || comando.izquierda || comando.derecha) {
			huboMovimientos = true;
			l->error("!!!!! " + std::to_string(comando.nroJugador) + " | " + std::to_string(comando.arriba) + " - " + std::to_string(comando.abajo) + " - " + std::to_string(comando.izquierda) + " - " + std::to_string(comando.derecha));
			*/
}

void sendData(std::list<HiloConexionServidor*>* hilosConexionesServidores, struct InformacionNivel* informacionNivel, struct EstadoTick* estadoTick, int* nuevoNivel) {
	if (*nuevoNivel) {
		l->debug("Nuevo nivel enviando : " + std::to_string(informacionNivel->numeroNivel));
	}

	if (*nuevoNivel) {
		for (auto *hiloConexionServidor : *(hilosConexionesServidores)) {
			hiloConexionServidor->enviarInformacionNivel(informacionNivel);
		}
		*nuevoNivel = false;
	} else {
		for (auto *hiloConexionServidor : *(hilosConexionesServidores)) {
			hiloConexionServidor->enviarEstadoTick(estadoTick);
		}
		*nuevoNivel = estadoTick->nuevoNivel;
	}
}

std::list<HiloConexionServidor*>* crearHilosConexionesServidores(std::list<ConexionServidor*>* conexiones) {
	auto* hilosConexionesServidores = new std::list<HiloConexionServidor*>();

	for (auto* conexion : *(conexiones)) {
		auto* hiloConexionServidor = new HiloConexionServidor(conexion);
		hiloConexionServidor->start();
		hilosConexionesServidores->push_back(hiloConexionServidor);
	}

	return hilosConexionesServidores;
}

void HiloOrquestadorPartida::run() {
	l->info("Comenzando a correr HiloOrquestadorPartida con " + std::to_string(conexiones->size()) + " jugadores.");
	bool quit = false;
	struct Comando comandos[conexiones->size()];
	struct InformacionNivel informacionNivel;
	struct EstadoTick estadoTick;
	bool terminoNivelActual = false;
	clock_t t2, t1 = clock();

	int commands_count = 0;
	initializeData(&estadoTick);
	// Todo esto es necesario?
	informacionNivel.numeroNivel = 0;
	// Comunicacion inicial.
	int nuevoNivel = 1;

	std::list<HiloConexionServidor*>* hilosConexionesServidores = crearHilosConexionesServidores(conexiones);
	for (int i = 0; i < hilosConexionesServidores->size(); i++) {
		struct Comando comando = comandos[i];
		comando = {0, 0, 0, 0, 0};
	}

	//keep communicating with client
	try {
		while (!quit) {

			// TODO
			// WIP. Para controlar la cantidad de ticks.
			t2 = clock();
			if ((t2 - t1) > 1000 * 1000 / 60 / 2) { // TODO jugar con estos valores afecta la performance, yo toco el ultimo nro para que sea divisor de 1 tick cada 60 sec.
				t1 = clock();
			} else {
				continue;
			}

			// Receive data (command)
			if (!receiveData(hilosConexionesServidores, comandos)) continue;
			//--------------------
			// Process model
			processData(partida, comandos, &estadoTick, &informacionNivel);
			//--------------------
			// Send data (view)
			sendData(hilosConexionesServidores, &informacionNivel, &estadoTick, &nuevoNivel);
			//--------------------
		}
	}
	catch (const std::exception& exc) {
		l->error("HiloOrquestadorPartida. Ocurrio un error en el main loop");
		// TODO stoppear hilosConexionesServidores
	}

	for (auto* hiloConexionServidor : *(hilosConexionesServidores)) {
		hiloConexionServidor->join();
	}

	l->info("Terminando de correr HiloOrquestadorPartida");
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
