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
#include "classes/HiloOrquestadorPartida.h"


#define BACKUP_CONFIG "../server/config/backup.json"

Log* l;

int esperarConexiones(int puerto, Configuracion* config);
Configuracion* parsearConfiguracion();


int main(int argc , char *argv[]) {
	l = new Log("server");

	Configuracion* config = parsearConfiguracion();
	std::string nivelLog = config->getNivelLog();
 	l->setConf(nivelLog);
	l->info("Iniciando el servidor.");

	return esperarConexiones(3040, config);
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


int esperarConexiones(int puerto, Configuracion* config) {
	l->info("Port: " + std::to_string(puerto));

	AceptadorConexiones* aceptadorConexiones = new AceptadorConexiones(puerto);
	aceptadorConexiones->escuchar();

	std::list<ConexionServidor*> conexiones;
	int jugadoresConectados = 0;

	while (conexiones.size() < config->getCantidadJugadores()) {
		l->info("Esperando usuario(s)");
		auto* conexionServidor = aceptadorConexiones->aceptarConexion();
		conexiones.push_back(conexionServidor);
		jugadoresConectados++;
		l->info("Usuario " + std::to_string(jugadoresConectados) + "conectado");
	}
	l->info("Todos los usuarios fueron aceptados");

	HiloOrquestadorPartida *hiloOrquestadorPartida;
	hiloOrquestadorPartida = new HiloOrquestadorPartida(config, conexiones);

	hiloOrquestadorPartida->start();

	hiloOrquestadorPartida->join();
	for (auto* conexion : conexiones) {
		conexion->cerrar();
	}
	printf("Client socket number closed\n");
	aceptadorConexiones->dejarDeEscuchar();
	printf("Server socket number closed\n");

	return 0;



	/*
	std::list<ConexionServidor*> conexiones;

	while (conexiones.size() < config->getCantidadJugadores()) {
		ConexionServidor* conexionServidor = aceptadorConexiones->aceptarConexion();
		if (conexionServidor == nullptr) {
			continue;
		}
		conexiones.push_back(conexionServidor);
		l->info("Connection " + std::to_string(conexiones.size()) + " accepted");
	}

	HiloOrquestadorPartida* hiloOrquestadorPartida = new HiloOrquestadorPartida(config, conexiones);

	hiloOrquestadorPartida->start();

	hiloOrquestadorPartida->join();

	for (auto* conexion : conexiones) {
		conexion->cerrar();
	}
	printf("Client socket number closed\n");
	aceptadorConexiones->dejarDeEscuchar();
	printf("Server socket number closed\n");

	return 0;
	 */
}
