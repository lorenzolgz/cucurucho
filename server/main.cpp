// !!!! Cambiar perrors y couts por logs
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
*/
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
// #include <stdbool.h>

#include <iostream>
#include <sys/socket.h>
// !!!! #include <netinet/in.h>
#include <arpa/inet.h>
// Structs for data transfer
#include "../commons/protocols/protocolo.h"
#include "../commons/connections/ConexionServidor.h"
#include "../commons/connections/AceptadorConexiones.h"
#include "../commons/utils/Log.h"
#include "classes/model/Partida.h"
#include "classes/config/ConfiguracionParser.h"

#define BACKUP_CONFIG "../server/config/backup.json"

Log* l;

void initializeData(struct View* client_view);
void processData(Partida* partida, struct Command action, struct View* view);
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
	std::cout << "Port: " + std::to_string(puerto) + "\n" << std::endl;

	AceptadorConexiones* aceptadorConexiones = new AceptadorConexiones(puerto);
	aceptadorConexiones->escuchar();
	ConexionServidor* coneccionServidor = aceptadorConexiones->aceptarConexion();

	// ConexionServidor* coneccionServidor = new ConexionServidor(client_socket);
	printf("Connection accepted\n\n");

	bool quit = false;
	struct Command client_command;
	struct View client_view;

	Partida* partida = new Partida(config);

	int commands_count = 0;
	int status = 0;
	initializeData(&client_view);

	//keep communicating with client
	while (!quit) {
		printf("Commands count: %d\n", commands_count + 1);

		// Receive data (command)
		client_command = coneccionServidor->recibirMensaje();
		printf("Incomming command action: \n");
		//--------------------

		// Process model
		processData(partida, client_command, &client_view);
		//--------------------

		// Send data (view)
		coneccionServidor->enviarMensaje(&client_view);
		printf("Send data: pos(X,Y) = (%d,%d)\n\n", client_view.positionX, client_view.positionY);
		//--------------------

		commands_count++;
	}

	coneccionServidor->cerrarConexion();
	printf("Client socket number closed\n");
	aceptadorConexiones->dejarDeEscuchar();
	printf("Server socket number closed\n");

	return status;
}

void processData(Partida* partida, struct Command command, struct View* view) {
	partida->tick(command);

	// !!!!
	if (command.arriba) (*view).positionY -= 2;
	if (command.abajo) (*view).positionY += 2;
	if (command.izquierda) (*view).positionX -= 2;
	if (command.derecha) (*view).positionX += 2;
}

void initializeData(struct View* client_view) {
	(*client_view).positionX = 0;
	(*client_view).positionY = 0;
}
