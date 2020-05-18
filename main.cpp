
#include <cstdlib>
#include <ctime>
#include <queue>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "classes/model/Jugador.h"
#include "classes/Log.h"
#include "classes/config/Configuracion.h"
#include "classes/GraphicRenderer.h"
#include "classes/model/Nivel.h"
#include "classes/config/NivelConfiguracion.h"
#include "classes/config/ConfiguracionParser.h"
#include "classes/model/ManagerNiveles.h"
#include "classes/model/Titulo.h"

#define BACKUP_CONFIG "../config/backup.json"

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

Configuracion* config;

Log l = Log();


void configurar(string archivoConfig, string nivelLog) {
	ConfiguracionParser configuracionParser;
	try {
		config = configuracionParser.parsearConfiguracion(archivoConfig);
	}
	catch (const std::exception& exc) {
        // Primero aviso que no se pudo usar el original antes de seguir con el backup
	    l.error("Ocurrió un error al leer el archivo de configuración, se usará el de backup");

        // Solo se loguean las excepciones que tengan un what() para poder dar mas info
        if ((exc.what()!= NULL) && (exc.what()[0] == '\0')){
            l.error(exc.what());
        }
        // Ahoro intento con el backup
        try {
            config = configuracionParser.parsearConfiguracion(BACKUP_CONFIG);
        }
        // Si el backup tampoco sirve, ya no puedo inicializar el juego
        catch (const std::exception& exc) {
            l.error("Ocurrio un error al leer el archivo de configuración de backup, no puede configurarse el juego");
            // Throw exception corta por completo la ejecucion del codigo
            throw exc;
        }

    }

	if (nivelLog.empty()) {
	    nivelLog = config->getNivelLog();
	}
	l.setConf(nivelLog);

    l.info("Alto pantalla: " + std::to_string(config->getAltoPantalla()));
    l.info("Ancho pantalla: " + std::to_string(config->getAnchoPantalla()));
    l.info("Escala pantalla: " + std::to_string(config->getEscalaPantalla()));
    l.info("Nivel de Log: " + nivelLog);
}


bool init() {
	int anchoPantalla = config->getAnchoPantalla();
	int altoPantalla = config->getAltoPantalla();
	int escalaPantalla = config->getEscalaPantalla();

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		l.error((std::string("No se logro inicializar SDL! SDL_Error: %s\n") + SDL_GetError()));
		return false;
	}

	// Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		l.debug("No se habilito el filro de la textura linear");
	}

	//Initialize SDL_image
	if (!(IMG_Init(IMG_INIT_PNG))) {
		l.error(std::string("No se logro inicializar SDL_image. SDL_image Error: ") + IMG_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow("Gley Lancer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							   anchoPantalla * escalaPantalla, altoPantalla * escalaPantalla, SDL_WINDOW_SHOWN);
	if (gWindow == nullptr) {
		l.error(std::string("La Ventana no creo correctamente! SDL_Error: ") + SDL_GetError());
		return false;
	}
	//Get window surface

	SDL_Renderer* gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == nullptr) {
		l.error(std::string("El Renderer no se creo correctamente! SDL_Error: ") + SDL_GetError());
		return false;
	}
	GraphicRenderer::setInstance(gRenderer);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND); // Para activar alpha/opacidad
	SDL_RenderSetScale(gRenderer, escalaPantalla, escalaPantalla);

	l.info("La ventana se creo correctamente");
	return true;
}


void close() {
	//Deallocate textures
	SDL_Renderer* gRenderer = GraphicRenderer::getInstance();
	SDL_DestroyRenderer(gRenderer);

	//Destroy window
	SDL_DestroyWindow(gWindow);

	//Free Configuration
	delete(config);

	l.info("Se libero toda la memoria");
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	l.info("La ventana se cerro correctamente");
}

void mainLoop() {
    int anchoPantalla = config->getAnchoPantalla();
	int altoPantalla = config->getAltoPantalla();
    bool quit = false;
    bool terminoNivelActual = false;
    SDL_Event e;
	Jugador* jugador = new Jugador(anchoPantalla / 8, altoPantalla / 2);
	ManagerNiveles* manager = new ManagerNiveles(config, jugador);
    Titulo* pantallaPrincipal = new Titulo(anchoPantalla, altoPantalla);

	l.info("Los objetos fueron inicializados correctamente a partir de los datos de la configuracion inicial");


    while (!quit) {
        const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

        //Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            //User requests quit
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }

        SDL_Renderer *gRenderer = GraphicRenderer::getInstance();
        //Clear screen
        SDL_RenderClear(gRenderer);

        // El usuario presiona ENTER o INTRO o ESPACIO
        bool onStart = currentKeyStates[SDL_SCANCODE_KP_ENTER] || currentKeyStates[SDL_SCANCODE_RETURN] || currentKeyStates[SDL_SCANCODE_SPACE];

        if (!pantallaPrincipal->isActivada(onStart)) {
            pantallaPrincipal->tick();
            SDL_RenderPresent(gRenderer);
            continue;
        }

        jugador->calcularVectorVelocidad(currentKeyStates[SDL_SCANCODE_UP],
                                         currentKeyStates[SDL_SCANCODE_DOWN],
                                         currentKeyStates[SDL_SCANCODE_LEFT],
                                         currentKeyStates[SDL_SCANCODE_RIGHT]);


        //Render texture to screen
		manager->tick();
		terminoNivelActual = manager->terminoNivelActual();
        if (terminoNivelActual) {
			terminoNivelActual = manager->pasajeDeNivel();
            SDL_RenderPresent(gRenderer);
            SDL_Delay(2000);
            quit = quit || manager->estadoJuego();
        } else {
			quit = quit || manager->estadoJuego();
			SDL_RenderPresent(gRenderer);
		}
    }
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

    std::string archivoConfig = BACKUP_CONFIG;
    std::string nivelLog;

    for (int i = 1; i < argc; i ++) {
        if (strcmp(argv[i], "-l") == 0) {
        	if (!validarParametroSimple(argc, argv, "-l", i)) {
                return -1;
            }
            if (!l.confValida(argv[i + 1])) {
                std::cout << "ERROR: nivel de log invalido: " + std::string(argv[i + 1]) + ". Los niveles validos son \"debug\", \"info\" y \"error\"" << std::endl;
                return -1;
            } else {
                nivelLog = std::string(argv[i + 1]);
            }
        } else if (strcmp(argv[i], "-c") == 0) {
			if (!validarParametroSimple(argc, argv, "-c", i)) return -1;
			archivoConfig = std::string(argv[i + 1]);
		} else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "--h") == 0) {
        	std::string help = "Gley Lancer en C++ by Cucurucho++\nCatedra Azcurra, Taller de Programacion I, Facultad de Ingenieria, UBA\n";
        	std::string opciones = "Opciones:\n\t-l\tSetea el nivel de log\n\t-c\tEspecifica ruta del archivo de configuracion (las rutas de imagenes que se utilicen son relativas a la carpeta \"assets/sprites\" del proyecto)";
			std::cout << help << std::endl;
			std::cout << opciones << std::endl;
			return 0;
		}
	}

    configurar(archivoConfig, nivelLog);

	// Inicializa SDL con la configuracion
	if (!init()) return 1;

	// Comienza el juego con la configuracion
	mainLoop();

	close();
	return 0;
}
