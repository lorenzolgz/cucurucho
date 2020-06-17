#include <iostream>
#include "../commons/protocols/protocolo.h"
#include "../commons/connections/ConexionServidor.h"
#include "../commons/connections/AceptadorConexiones.h"
#include "classes/config/ConfiguracionParser.h"
#include "classes/config/FondoConfiguracion.h"
#include "classes/HiloOrquestadorPartida.h"
#include "../commons/connections/ControladorDeSesiones.h"
#include "../commons/connections/ConexionExcepcion.h"


#define BACKUP_CONFIG "../server/config/backup.json"

Log* l;

int esperarConexiones(int puerto, Configuracion* config);
Configuracion* parsearConfiguracion();
bool validarParametroSimple(int argc, char *argv[], std::string parametro, int posArg);


int main(int argc , char *argv[]) {

    // TODO: Recibir los parametros se dejo en el cliente y nunca se trajo al server
    // Faltan traer nivel de log y archivo de configuracion

    int port = 3040;

    for (int i = 1; i < argc; i ++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "--h") == 0) {
            std::string help = "Gley Lancer (servidor) en C++ by Cucurucho++\nCatedra Azcurra, Taller de Programacion I, Facultad de Ingenieria, UBA\n";
            // TODO: Ver si falta actualizar el help
            std::string opciones = std::string("Opciones:\n\t")
                                   + "-l\tSetea el nivel de log\n\t"
                                   + "-c\tEspecifica ruta del archivo de configuracion (las rutas de imagenes que se utilicen son relativas a la carpeta \"assets/sprites\" del proyecto)"
                                   + "-p\tEspecifica el puerto sobre el cual va a correr el servidor";
            std::cout << help << std::endl;
            std::cout << opciones << std::endl;
            return 0;
        } else if (strcmp(argv[i], "-p") == 0) {
            if (!validarParametroSimple(argc, argv, "-p", i)) {
                return -1;
            }
            int new_port = atoi(argv[i + 1]);
            if (new_port < 1024 || new_port > 49151) {
                std::cout << "Numero de puerto invalido" << std::endl;
                return -1;
            }
            port = new_port;
        }
    }

    l = new Log("server");

	Configuracion* config = parsearConfiguracion();
	std::string nivelLog = config->getNivelLog();
 	l->setConf(nivelLog);
	l->info("Iniciando el conexionServidor.");

	return esperarConexiones(port, config);
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
		l->error("Ocurrio un error alhilocon leer el archivo de configuración de backup, no puede configurarse el juego");
		// Throw exception corta por completo la ejecucion del codigo
		throw exc;
	}

	return config;
}


void notificarEstadoConexion(std::list<ConexionServidor*>* conexiones, int estadoLogin) {
    nlohmann::json json;
    json["tipoMensaje"] = ESTADO_LOGIN;
    json["estadoLogin"] = estadoLogin;
    json["jugador1"] = "\0";
    json["jugador2"] = "\0";
    json["jugador3"] = "\0";
    json["jugador4"] = "\0";

    int i = 1;
    for (ConexionServidor* & c : *conexiones) {
        json["jugador" + std::to_string(i)] = c->getUsuario();
        i++;
    }

    i = 1;
    auto j = conexiones->begin();
    while (j != conexiones->end()) {
        try {
            json["nroJugador"] = i;
            (*j)->enviarMensaje(json);
            j++;
            i++;
        } catch (const ConexionExcepcion& e) {
            // Si el usuario se desconecta antes de comenzar la partida puede conectarse otro (evaluar?)
            conexiones->erase(j);
            // Volver a enviar mensajes con lista actualizada
            notificarEstadoConexion(conexiones, estadoLogin);
            return;
        }
    }
}


int esperarConexiones(int puerto, Configuracion* config) {
	l->info("Port: " + std::to_string(puerto));

	AceptadorConexiones* aceptadorConexiones = new AceptadorConexiones(puerto);
	aceptadorConexiones->escuchar();

	std::list<ConexionServidor*> conexiones;

	while (conexiones.size() < config->getCantidadJugadores()) { //usuario != usuarioPerdido
		l->info("Esperando usuario(s)");
		auto* conexionServidor = aceptadorConexiones->aceptarConexion();
		ControladorDeSesiones* controladorDeSesiones = new ControladorDeSesiones(conexionServidor, conexiones, conexiones.size()+1);
        if (!controladorDeSesiones->iniciarSesion()) {//si entró un usuario no registrado
            continue;
        }
        conexiones.push_back(conexionServidor);
        notificarEstadoConexion(&conexiones, LOGIN_ESPERAR);
        l->info("Usuario " + std::to_string(conexiones.size()) + " conectado");
	}
	l->info("Todos los usuarios fueron aceptados");
    notificarEstadoConexion(&conexiones, LOGIN_COMENZAR);

    // TODO: Pre-procesamiento?
    std::this_thread::sleep_for(std::chrono::seconds(TIMEOUT_LOGIN_FIN));
    notificarEstadoConexion(&conexiones, LOGIN_FIN);

	HiloOrquestadorPartida* hiloOrquestadorPartida = new HiloOrquestadorPartida(config, &conexiones, aceptadorConexiones);

	try {
		hiloOrquestadorPartida->start();

		hiloOrquestadorPartida->join();
	} catch (const std::exception& exc) {
		l->error("HiloAceptador. main");
	}

	for (auto* conexion : conexiones) {
		conexion->cerrar();
	}
	l->info("Client socket number closed\n");
	aceptadorConexiones->dejarDeEscuchar();
	l->info("Server socket number closed\n");

	return 0;
}


bool validarParametroSimple(int argc, char *argv[], std::string parametro, int posArg) {
    if (posArg + 1 >= argc || argv[posArg+1][0] == '-') {
        std::cout << "ERROR: falto pasar un parametro para la opcion \"" + parametro + "\"" << std::endl;
        return false;
    }

    return true;
}
