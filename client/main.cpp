
#include <cstdlib>
#include <ctime>
#include <queue>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "classes/Log.h"
#include "classes/GraphicRenderer.h"
#include "classes/model/Nivel.h"
#include "classes/view/Titulo.h"
#include "classes/view/JugadorVista.h"
#include "classes/view/ManagerVista.h"
#include "classes/config/ConfiguracionParser.h"

#define BACKUP_CONFIG "../config/backup.json"

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

Log* l;


void configurar(std::string nivelLog) {
	if (!nivelLog.empty()) {
        l->setConf(nivelLog);
    }

    l->info("Alto pantalla: " + std::to_string(PANTALLA_ALTO));
    l->info("Ancho pantalla: " + std::to_string(PANTALLA_ANCHO));
    l->info("Escala pantalla: " + std::to_string(1));
    l->info("Nivel de Log: " + nivelLog);
}


bool init() {
	int anchoPantalla = PANTALLA_ANCHO;
	int altoPantalla = PANTALLA_ALTO;
	int escalaPantalla = 1;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		l->error((std::string("No se logro inicializar SDL! SDL_Error: %s\n") + SDL_GetError()));
		return false;
	}

	// Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		l->debug("No se habilito el filro de la textura linear");
	}

	//Initialize SDL_image
	if (!(IMG_Init(IMG_INIT_PNG))) {
		l->error(std::string("No se logro inicializar SDL_image. SDL_image Error: ") + IMG_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow("Gley Lancer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							   anchoPantalla * escalaPantalla, altoPantalla * escalaPantalla, SDL_WINDOW_SHOWN);
	if (gWindow == nullptr) {
		l->error(std::string("La Ventana no creo correctamente! SDL_Error: ") + SDL_GetError());
		return false;
	}
	//Get window surface

	SDL_Renderer* gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == nullptr) {
		l->error(std::string("El Renderer no se creo correctamente! SDL_Error: ") + SDL_GetError());
		return false;
	}
	GraphicRenderer::setInstance(gRenderer);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    SDL_SetRenderDrawBlendMode(gRenderer, SDL_BLENDMODE_BLEND); // Para activar alpha/opacidad
	SDL_RenderSetScale(gRenderer, escalaPantalla, escalaPantalla);

	l->info("La ventana se creo correctamente");
	return true;
}


void close() {
	//Deallocate textures
	SDL_Renderer* gRenderer = GraphicRenderer::getInstance();
	SDL_DestroyRenderer(gRenderer);

	//Destroy window
	SDL_DestroyWindow(gWindow);

	l->info("Se libero toda la memoria");
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	l->info("La ventana se cerro correctamente");
}

std::vector<NivelConfiguracion*> mockConfig() {
    std::vector<NivelConfiguracion*> nivelConfig;
    nivelConfig.push_back(new NivelConfiguracion(ConfiguracionParser().parsearArchivoFondos("fondos/fondos1.json", 0), "cleared_con_nave1.png", 2, 36000));
    return nivelConfig;
}

void mainLoop() {
    int anchoPantalla = PANTALLA_ANCHO;
	int altoPantalla = PANTALLA_ALTO;
    bool quit = false;
    bool terminoNivelActual = false;
    SDL_Event e;
	JugadorVista* jugador = new JugadorVista(COLORES_AZUL);
	ManagerVista* manager = new ManagerVista(jugador, mockConfig(), 0, anchoPantalla, altoPantalla);
    Titulo* pantallaPrincipal = new Titulo(anchoPantalla, altoPantalla);

	l->info("Los objetos fueron inicializados correctamente a partir de los datos de la configuracion inicial");


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

//        jugador->calcularVectorVelocidad(currentKeyStates[SDL_SCANCODE_UP],
//                                         currentKeyStates[SDL_SCANCODE_DOWN],
//                                         currentKeyStates[SDL_SCANCODE_LEFT],
//                                         currentKeyStates[SDL_SCANCODE_RIGHT]);


        //Render texture to screen
		manager->render();
        jugador->render(Vector(200, 200), 0);
		SDL_RenderPresent(gRenderer);
//		terminoNivelActual = manager->terminoNivelActual();
//        if (terminoNivelActual) {
//			terminoNivelActual = manager->pasajeDeNivel();
//            SDL_RenderPresent(gRenderer);
//            SDL_Delay(2000);
//            quit = quit || manager->estadoJuego();
//        } else {
//			quit = quit || manager->estadoJuego();
//			SDL_RenderPresent(gRenderer);
//		}
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
        	std::string help = "Gley Lancer en C++ by Cucurucho++\nCatedra Azcurra, Taller de Programacion I, Facultad de Ingenieria, UBA\n";
        	std::string opciones = "Opciones:\n\t-l\tSetea el nivel de log\n\t-c\tEspecifica ruta del archivo de configuracion (las rutas de imagenes que se utilicen son relativas a la carpeta \"assets/sprites\" del proyecto)";
			std::cout << help << std::endl;
			std::cout << opciones << std::endl;
			return 0;
		}
	}

    l = new Log();
    configurar(nivelLog);

	// Inicializa SDL con la configuracion
	if (!init()) return 1;

	// Comienza el juego con la configuracion
	mainLoop();

	close();
	return 0;
}
