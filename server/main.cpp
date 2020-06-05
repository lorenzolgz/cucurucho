#include <time.h>
#include <iostream>
#include "../commons/protocols/protocolo.h"
#include "../commons/connections/ConexionServidor.h"
#include "../commons/connections/AceptadorConexiones.h"
#include "../commons/utils/Log.h"
#include "classes/model/Partida.h"
#include "classes/config/ConfiguracionParser.h"
#include "../commons/connections/ControladorDeSesiones.h"

#define BACKUP_CONFIG "../server/config/backup.json"

Log* l;

void initializeData(struct EstadoTick* estadoTick);
void processData(Partida* partida, struct Comando action, struct InformacionNivel* informacionNivel, struct EstadoTick* estadoTick);
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


	 //logueo con user y password
	 ControladorDeSesiones* controlador = new ControladorDeSesiones(conexionServidor);
	 controlador->iniciarSesion();
     //

	bool quit = false;
	struct Comando client_command;
	struct InformacionNivel informacionNivel;
	struct EstadoTick estadoTick;
	clock_t t2, t1 = clock();

	Partida* partida = new Partida(config);

	int commands_count = 0;
	int status = 0;
	initializeData(&estadoTick);

	// Comunicacion inicial.
	int nuevoNivel = 1;
	bool closedSocket = false;

	//keep communicating with client
	while (!quit) {

        // Reaching this point means the client socket has been closed
        // and the server is no longer available to write on the client socket
	    /*if(closedSocket){
            conexionServidor->cerrarConexion();
            printf("Client socket closed\n");
            conexionServidor = aceptadorConexiones->aceptarConexion();
            // conexionServidor = aceptadorConexiones->aceptarConexion();
            closedSocket = false;
        }*/

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
		processData(partida, client_command, &informacionNivel, &estadoTick);
		//--------------------

		if (nuevoNivel) {
			l->info("Enviando nuevo nivel:" + std::to_string(nuevoNivel));
		}

		// Send data (view)
		if (nuevoNivel) {
			if(conexionServidor->enviarInformacionNivel(&informacionNivel) < 0){
			    conexionServidor = aceptadorConexiones->reconectar();
			}
            nuevoNivel = false;
        } else {
            if(conexionServidor->enviarEstadoTick(&estadoTick) < 0){
                conexionServidor = aceptadorConexiones->reconectar();
            }
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

void processData(Partida* partida, struct Comando command, struct InformacionNivel* informacionNivel, struct EstadoTick* estadoTick) {
	partida->tick(command);
	EstadoInternoNivel estadoInternoNivel = partida->state();

	// Seteando informacionNivel
	informacionNivel->muchaData = estadoInternoNivel.nuevoNivel;

	// Seteando estadoTick
	estadoTick->nuevoNivel = estadoInternoNivel.nuevoNivel;
	EstadoInternoCampoMovil estadoCampoMovil = estadoInternoNivel.estadoCampoMovil;
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
