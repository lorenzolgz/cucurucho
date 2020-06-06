#include <time.h>
#include <iostream>
#include <cstring>
#include "../commons/protocols/protocolo.h"
#include "../commons/connections/ConexionServidor.h"
#include "../commons/connections/AceptadorConexiones.h"
#include "../commons/utils/Log.h"
#include "classes/model/Partida.h"
#include "classes/config/ConfiguracionParser.h"
#include "classes/config/FondoConfiguracion.h"


#define BACKUP_CONFIG "../server/config/backup.json"

Log* l;

void initializeData(struct EstadoTick* estadoTick);
void procesarNivel(struct InformacionNivel* informacionNivel, Partida* partida);
void processData(Partida* partida, struct Comando action,struct EstadoTick* estadoTick, struct InformacionNivel* informacionNivel);
void processNivel(struct InformacionNivel* informacionNivel);
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
	ConexionServidor* conexionServidor = aceptadorConexiones->aceptarConexion();

	// ConexionServidor* conexionServidor = new ConexionServidor(client_socket);
	l->info("Connection accepted");

	bool quit = false;
	struct Comando client_command;
	struct InformacionNivel informacionNivel;
	struct EstadoTick estadoTick;
    bool terminoNivelActual = false;
	clock_t t2, t1 = clock();

	Partida* partida = new Partida(config);

	int commands_count = 0;
	int status = 0;
    initializeData(&estadoTick);
    informacionNivel.numeroNivel = 0;

    // Comunicacion inicial.
	int nuevoNivel = 1;

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
		client_command = conexionServidor->recibirMensaje();
		// printf("Incomming command action: \n");
		//--------------------

		// Process model
        processData(partida, client_command, &estadoTick, &informacionNivel);
        //--------------------

		if (nuevoNivel) {
            l->debug("Nuevo nivel enviando : " + std::to_string(informacionNivel.numeroNivel));
		}

		// Send data (view)
		if (nuevoNivel) {
			conexionServidor->enviarInformacionNivel(&informacionNivel);
			nuevoNivel = false;
		} else {
			conexionServidor->enviarEstadoTick(&estadoTick);
			nuevoNivel = estadoTick.nuevoNivel;
		}
		// printf("Send data: pos(X,Y) = (%d,%d)\n\n", client_view.posicionX, client_view.posicionY);
		//--------------------

		commands_count++;

	}

	conexionServidor->cerrarConexion();
	printf("Client socket number closed\n");
	aceptadorConexiones->dejarDeEscuchar();
	printf("Server socket number closed\n");

	return status;
}


void processData(Partida* partida, struct Comando command, struct EstadoTick* estadoTick, struct InformacionNivel* informacionNivel) {
	EstadoInternoNivel estadoInternoNivel = partida->state(informacionNivel);
    partida->tick(command);

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
