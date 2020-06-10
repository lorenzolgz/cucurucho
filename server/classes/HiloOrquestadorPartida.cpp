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

void receiveData(std::list<HiloConexionServidor*>* hilosConexionesServidores, struct Comando *comandos) {
	int contadorColasReceptoras = 0;
	for (auto* hiloConexionServidor : *(hilosConexionesServidores)) {
		auto* colaReceptora = hiloConexionServidor->colaReceptora;
		nlohmann::json mensajeJson = colaReceptora->pop();
		if (mensajeJson["_t"] == COMANDO) {
			struct Comando comando = {mensajeJson["arriba"], mensajeJson["abajo"], mensajeJson["izquierda"], mensajeJson["derecha"]};
			// TODO muuy turbina esto, solucionar mandando nro de cliente, despues de hacer la autenticacion!!!!
			comandos[contadorColasReceptoras] = comando;
			contadorColasReceptoras++;
		} else {
			l->error("HiloOrquestadorPartida. Recibiendo mensaje invalido");
		}
	}
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
	l->info("Comenzando a correr HiloOrquestadorPartida");
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

	//keep communicating with client
	try {
		while (!quit) {

			// TODO
			// WIP. Para controlar la cantidad de ticks.
			t2 = clock();
			if ((t2 - t1) > 50) {
				//DO the stuff!
				// printf("!!!! %d\n", t2-t1);i
				t1 = clock();
			}

			// Receive data (command)
			receiveData(hilosConexionesServidores, comandos);
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
	}

	for (auto* hiloConexionServidor : *(hilosConexionesServidores)) {
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
