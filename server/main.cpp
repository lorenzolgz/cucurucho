#include <iostream>
#include "../commons/protocols/protocolo.h"
#include "../commons/connections/ConexionServidor.h"
#include "../commons/connections/AceptadorConexiones.h"
#include "classes/config/ConfiguracionParser.h"
#include "classes/config/FondoConfiguracion.h"
#include "classes/HiloOrquestadorPartida.h"
#include "classes/HiloAceptadorConexiones.h"


#define BACKUP_CONFIG "../server/config/backup.json"

Log* l;

int esperarConexiones(int puerto, Configuracion* config);
Configuracion* parsearConfiguracion(std::string archivoConfig, bool &std_out);
bool validarParametroSimple(int argc, char *argv[], std::string parametro, int posArg);
std::list<HiloConexionServidor*>* crearHilosConexionesServidores(std::list<ConexionServidor*>* conexiones,
                                                                 AceptadorConexiones* aceptadorConexiones);


int main(int argc , char *argv[]) {

    // TODO: Recibir los parametros se dejo en el cliente y nunca se trajo al server
    // Faltan traer nivel de log y archivo de configuracion
    std::string archivoConfig;
    std::string nivelLog = "";
    int port = 3040;

    for (int i = 1; i < argc; i ++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "--h") == 0) {
            std::string help = "Gley Lancer (servidor) en C++ by Cucurucho++\nCatedra Azcurra, Taller de Programacion I, Facultad de Ingenieria, UBA\n";
            // TODO: Ver si falta actualizar el help
            std::string opciones = std::string("Opciones:\n\t")
                                   + "-l\tSetea el nivel de log\n\t"
                                   + "-c\tEspecifica ruta del archivo de configuracion (las rutas de imagenes que se utilicen son relativas a la carpeta \"assets/sprites\" del proyecto)\n\t"
                                   + "-p\tEspecifica el puerto sobre el cual va a correr el servidor\n\t";
            std::cout << help << std::endl;
            std::cout << opciones << std::endl;
            return 0;
        } else if (strcmp(argv[i], "-l") == 0) {
            if (!validarParametroSimple(argc, argv, "-l", i)) {
                return -1;
            }
            if (!Log::confValida(argv[i + 1])) {
                std::cout << "ERROR: nivel de log invalido: " + std::string(argv[i + 1]) + ". Los niveles validos son \"debug\", \"info\" y \"error\"" << std::endl;
                return -1;
            } else {
                nivelLog = std::string(argv[i + 1]);
            }
        } else if (strcmp(argv[i], "-c") == 0) {
            if (!validarParametroSimple(argc, argv, "-c", i)) return -1;
            archivoConfig = std::string(argv[i + 1]);
        }else if (strcmp(argv[i], "-p") == 0) {
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

    bool std_out;

    Configuracion* config = parsearConfiguracion(archivoConfig, std_out);
    if (nivelLog == "") nivelLog = config->getNivelLog();
    l->set_stdout(std_out);
    l->setConf(nivelLog);
    l->info("Iniciando el conexionServidor.");

    return esperarConexiones(port, config);
}

Configuracion* parsearConfiguracion(std::string archivoConfig, bool &std_out) {
    ConfiguracionParser configuracionParser;
    Configuracion* config;

    try {
        config = configuracionParser.parsearConfiguracion(archivoConfig);
    }
    catch (const std::exception& exc) {
        l->error("Ocurrio un error al leer el archivo de configuración, intento con backup");
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
    }

    std_out = configuracionParser.std_out;
    return config;
}


int esperarConexiones(int puerto, Configuracion* config) {
	l->info("Puerto: " + std::to_string(puerto));

    HiloAceptadorConexiones* hiloAceptadorConexiones = new HiloAceptadorConexiones(puerto, config);

    hiloAceptadorConexiones->start();
    hiloAceptadorConexiones->join();

	return 0;
}


bool validarParametroSimple(int argc, char *argv[], std::string parametro, int posArg) {
    if (posArg + 1 >= argc || argv[posArg+1][0] == '-') {
        std::cout << "ERROR: falto pasar un parametro para la opcion \"" + parametro + "\"" << std::endl;
        return false;
    }

    return true;
}