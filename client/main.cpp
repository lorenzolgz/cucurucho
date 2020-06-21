#include <cstdlib>
#include <ctime>
#include <queue>
#include "../commons/utils/Log.h"
#include "classes/GraphicRenderer.h"
#include "../commons/connections/IniciadorComunicacion.h"
#include "../server/classes/states/EstadoInternoNivel.h"
#include "../commons/utils/Constantes.h"
#include "classes/GestorSDL.h"
#include "classes/Partida.h"
#include "classes/config/Configuracion.h"
#include "classes/config/ConfiguracionParser.h"

#define BACKUP_CONFIG"../client/config/backup.json"

Log* l;
ToastVista* toast;

void configurar(std::string nivelLog) {
    l->setConf(nivelLog);

    l->info("Alto pantalla: " + std::to_string(PANTALLA_ALTO));
    l->info("Ancho pantalla: " + std::to_string(PANTALLA_ANCHO));
    l->info("Escala pantalla: " + std::to_string(1));
    l->info("Nivel de Log: " + nivelLog);
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
        std::cout<<"Ocurrio un error alhilocon leer el archivo de configuración de backup, no puede configurarse el juego"<<std::endl;
        // Throw exception corta por completo la ejecucion del codigo
        throw exc;
    }

    return config;
}

bool validarParametroSimple(int argc, char *argv[], std::string parametro, int posArg) {
	if (posArg + 1 >= argc || argv[posArg+1][0] == '-') {
		std::cout << "ERROR: falto pasar un parametro para la opcion \"" + parametro + "\"" << std::endl;
		return false;
	}

	return true;
}

int main(int argc, char *argv[]) {
    std::srand(std::time(NULL)); //use current time as seed for random generator

    std::string archivoConfig;
    Configuracion* config = parsearConfiguracion();
    std::string nivelLog = config->getNivelLog();

    int port = 3040;
    std::string dir_ip = "127.0.0.1";

    GestorSDL* gestorSDL = new GestorSDL();
    Partida* partida = new Partida();

    for (int i = 1; i < argc; i ++) {
        if (strcmp(argv[i], "-l") == 0) {
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
		} else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "--h") == 0) {
            std::string help = "Gley Lancer (cliente) en C++ by Cucurucho++\nCatedra Azcurra, Taller de Programacion I, Facultad de Ingenieria, UBA\n";
            std::string opciones = std::string("Opciones:\n\t")
                                   + "-l\tSetea el nivel de log\n\t"
                                   + "-c\tEspecifica ruta del archivo de configuracion (las rutas de imagenes que se utilicen son relativas a la carpeta \"assets/sprites\" del proyecto)"
                                   + "-h\tEspecifica la direccion IP a la cual conectarse"
                                   + "-p\tEspecifica el puerto a conectarse";
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
        } else if (strcmp(argv[i], "-h") == 0) {
            if (!validarParametroSimple(argc, argv, "-h", i)) {
                return -1;
            }
            dir_ip = std::string(argv[i + 1]);
        }
	}

    l = new Log("client");
    configurar(nivelLog);

	// Inicializa SDL con la configuracion
	if (!gestorSDL->init(PANTALLA_ANCHO, PANTALLA_ALTO)) return 1;

	// Comienza el juego con la configuracion
	partida->play(dir_ip.c_str(), port);

    gestorSDL->close();
	return 0;
}
