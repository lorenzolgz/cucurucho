#include <time.h>
#include <iostream>
#include "../commons/protocols/protocolo.h"
#include "../commons/connections/ConexionServidor.h"
#include "../commons/connections/AceptadorConexiones.h"
#include "../commons/utils/Log.h"
#include "classes/model/Partida.h"
#include "classes/config/ConfiguracionParser.h"

#define BACKUP_CONFIG "../server/config/backup.json"

Log* l;

void initializeData(struct EstadoTick* estadoTick);
void processData(Partida* partida, struct Comando action, struct EstadoTick* estadoTick);
int mainLoop(int puerto, Configuracion* configuracion);
Configuracion* parsearConfiguracion();


int main(int argc , char *argv[]) {
	l = new Log("server");

	Configuracion* config = parsearConfiguracion();
	std::string nivelLog = config->getNivelLog();
 	l->setConf(nivelLog);
	l->info("Iniciando el servidor.");

	return mainLoop(3040, config);
}

Configuracion* parsearConfiguracion() {
	ConfiguracionParser configuracionParser;
	Configuracion* config;

	// Ahoro intento con el backup
	try {
		config = configuracionParser.parsearConfiguracion(BACKUP_CONFIG);
	}
		// Si el backup tampoco sirve, ya no puedo inicializar el juego
	catch (const std::exception& exc) {
		l->error("Ocurrio un error al leer el archivo de configuración de backup, no puede configurarse el juego");
		// Throw exception corta por completo la ejecucion del codigo
		throw exc;
	}

	return config;
}

int mainLoop(int puerto, Configuracion* config) {
	l->info("Port: " + std::to_string(puerto));

	AceptadorConexiones* aceptadorConexiones = new AceptadorConexiones(puerto);
	aceptadorConexiones->escuchar();
	ConexionServidor* coneccionServidor = aceptadorConexiones->aceptarConexion();

	// ConexionServidor* coneccionServidor = new ConexionServidor(client_socket);
	l->info("Connection accepted");

	bool quit = false;
	struct Comando client_command;
	struct EstadoTick estadoTick;
	clock_t t2, t1 = clock();

	Partida* partida = new Partida(config);

	int commands_count = 0;
	int status = 0;
	initializeData(&estadoTick);

	//keep communicating with client
	while (!quit) {

		// WIP. Para controlar la cantidad de ticks.
		t2 = clock();
		if((t2-t1) > 50) {
			//DO the stuff!
			// printf("!!!! %d\n", t2-t1);
			t1 = clock();
		}

		// printf("Commands count: %d\n", commands_count + 1);

		// Receive data (command)
		client_command = coneccionServidor->recibirMensaje();
		// printf("Incomming command action: \n");
		//--------------------

		// Process model
		processData(partida, client_command, &estadoTick);
		//--------------------

		// Send data (view)
		coneccionServidor->enviarMensaje(&estadoTick);
		// printf("Send data: pos(X,Y) = (%d,%d)\n\n", client_view.posicionX, client_view.posicionY);
		//--------------------

		commands_count++;
	}

	coneccionServidor->cerrarConexion();
	printf("Client socket number closed\n");
	aceptadorConexiones->dejarDeEscuchar();
	printf("Server socket number closed\n");

	return status;
}

void processData(Partida* partida, struct Comando command, struct EstadoTick* estadoTick) {
	partida->tick(command);
	EstadoCampoMovil estadoCampoMovil = partida->state();
	estadoTick->estadoJugador = estadoCampoMovil.estadoJugador;
	int i = 0;
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
	estadoTick->estadoJugador.posicionX = -1000;
	estadoTick->estadoJugador.posicionY = -1000;
	estadoTick->estadoJugador.contadorVelocidadY = 0;

	estadoTick->estadoJugador.helper1.posicionX = -1000;
	estadoTick->estadoJugador.helper1.posicionY = -1000;
	estadoTick->estadoJugador.helper1.angulo = 0;

	estadoTick->estadoJugador.helper2.posicionX = -1000;
	estadoTick->estadoJugador.helper2.posicionY = -1000;
	estadoTick->estadoJugador.helper2.angulo = 0;

	for (int i = 0; i < MAX_ENEMIGOS; i++) {
		estadoTick->estadosEnemigos[i].clase = 0;
	}
}
