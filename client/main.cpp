
#include <cstdlib>
#include <ctime>
#include <queue>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../commons/utils/Log.h"
#include "classes/GraphicRenderer.h"
#include "classes/view/Titulo.h"
#include "classes/view/JugadorVista.h"
#include "classes/view/ManagerVista.h"
#include "classes/config/ConfiguracionParser.h"
#include "../commons/connections/ConexionCliente.h"
#include "../commons/connections/IniciadorComunicacion.h"
#include "classes/config/NivelConfiguracion.h"
#include "../server/classes/states/EstadoInternoNivel.h"
#include "../commons/utils/Constantes.h"

#define BACKUP_CONFIG "../config/backup.json"

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

Log* l;
ToastVista* toast;

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
    toast = new ToastVista();

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


// Manejar eventos (teclas, texto) de SDL
// Si se cumple `SDL_QUIT`, devuelve true.
bool eventLoop(std::string* inputText) {
    bool quit = false;
    SDL_Event e;

    //Handle events on queue
    while (SDL_PollEvent(&e) != 0) {
        //User requests quit
        if (e.type == SDL_QUIT) {
            quit = true;
        } else if (e.type == SDL_TEXTINPUT) {
            *inputText += e.text.text;
        } else if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_BACKSPACE) {
                *inputText += 8;
            } else if (e.key.keysym.sym == SDLK_UP) {
                *inputText += 9;
            } else if (e.key.keysym.sym == SDLK_DOWN) {
                *inputText += 10;
            } else if (e.key.keysym.sym == SDLK_KP_ENTER || e.key.keysym.sym == SDLK_RETURN) {
                *inputText += 11;
            } else if (e.key.keysym.sym == SDLK_d && (SDL_GetModState() & KMOD_CTRL)) {
                *inputText += 12;
            }
        }
    }

    return quit;
}


// Muestra la pantalla de logueo
// En el caso que se haya rechazado la conexion, se vuelve a establecer
bool pantallaInicioLoop(IniciadorComunicacion* iniciadorComunicacion, ConexionCliente** conexionCliente,
        Titulo *pantallaPrincipal, std::string inputText, const Uint8 *currentKeyStates) {

    // El usuario presiona ENTER o INTRO o ESPACIO
    bool onStart = currentKeyStates[SDL_SCANCODE_KP_ENTER] || currentKeyStates[SDL_SCANCODE_RETURN] || currentKeyStates[SDL_SCANCODE_SPACE];

    if (!pantallaPrincipal->isActivada(onStart)) {
        if (pantallaPrincipal->tick(inputText, *conexionCliente)) {
            (*conexionCliente)->cerrarConexion();
            *conexionCliente = iniciadorComunicacion->conectar();
        }
        SDL_RenderPresent(GraphicRenderer::getInstance());
        return true;
    }

    return false;
}


// Comunicacion con el cliente.
// Primero envia la secuencia de teclas presionada, y despues recibe informacion del servidor
// Si `nuevoNivel` es true, debe recibir el nivel en vez de la informacion del escenario (!!)
ConexionCliente* conexionLoop(ConexionCliente* conexionCliente,
                                struct EstadoTick* estadoTick, struct InformacionNivel* informacionNivel, bool* nuevoNivel,
                                const Uint8 *currentKeyStates) {

    struct Comando client_command = { false, false, false, false };

    client_command.arriba = currentKeyStates[SDL_SCANCODE_UP];
    client_command.abajo = currentKeyStates[SDL_SCANCODE_DOWN];
    client_command.izquierda = currentKeyStates[SDL_SCANCODE_LEFT];
    client_command.derecha = currentKeyStates[SDL_SCANCODE_RIGHT];
    // Send data (command)
    conexionCliente->enviarMensaje(&client_command);

    if (*nuevoNivel) {
        *informacionNivel = conexionCliente->recibirInformacionNivel();
        l->debug("Nuevo nivel recibido : " + std::to_string(informacionNivel->numeroNivel));
        *nuevoNivel = false;
    } else {
        *estadoTick = conexionCliente->recibirEstadoTick();
        *nuevoNivel = estadoTick->nuevoNivel;
    }

    return conexionCliente;
}

// Renderiza el juego. Devuelve `false` si llego al nivel final (para salir del juego)
// TODO: Hardcodeadisimo. Cambiar.
bool renderLoop(ManagerVista* manager, struct EstadoTick estadoTick, struct InformacionNivel informacionNivel, bool nuevoNivel) {

    bool quit = false;

    manager->setInformacionNivel(informacionNivel);
    //Render texture to screen
    manager->render(estadoTick);

    if (nuevoNivel) {
        manager->renderNivelIntermedio();
        SDL_RenderPresent(GraphicRenderer::getInstance());
        SDL_Delay(2000);
        // Harcodeadisimo para que termine en el ultimo nivel
        // TODO: Y tambien funciona mal. please reevaluar.
        quit = quit || informacionNivel.numeroNivel > 3;
    } else {
        quit = quit || informacionNivel.numeroNivel > 3;
        SDL_RenderPresent(GraphicRenderer::getInstance());
    }

    return quit;
}


void mainLoop() {
    int anchoPantalla = PANTALLA_ANCHO;
	int altoPantalla = PANTALLA_ALTO;
    bool quit = false;

    ManagerVista* manager = new ManagerVista({}, 0, anchoPantalla, altoPantalla);
    Titulo* pantallaPrincipal = new Titulo(anchoPantalla, altoPantalla);

	// !!!!
	//------------------------
	// BEGIN socket configuration
    struct EstadoTick estadoTick;
    struct InformacionNivel informacionNivel;

	bool nuevoNivel = true;
	char* ip_address = (char*) "127.0.0.1";
	int port = 3040;
    IniciadorComunicacion* iniciadorComunicacion = new IniciadorComunicacion(ip_address, port);
    ConexionCliente* conexionCliente = iniciadorComunicacion->conectar();

    l->info("Los objetos fueron inicializados correctamente a partir de los datos de la configuracion inicial");

    while (!quit) {
        const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
        SDL_RenderClear(GraphicRenderer::getInstance());

        std::string inputText;
        quit = quit || eventLoop(&inputText);

        // TODO: Separar mejor el logueo conexion del logueo vista
        if (pantallaInicioLoop(iniciadorComunicacion, &conexionCliente, pantallaPrincipal, inputText, currentKeyStates)) {
            continue;
        }

        if (!conexionLoop(conexionCliente, &estadoTick, &informacionNivel, &nuevoNivel, currentKeyStates)) {
            continue;
        }

        quit = quit || renderLoop(manager, estadoTick, informacionNivel, nuevoNivel);
    }

    if (conexionCliente != nullptr) {
        conexionCliente->cerrarConexion();
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

    l = new Log("client");
    configurar(nivelLog);

	// Inicializa SDL con la configuracion
	if (!init()) return 1;

	// Comienza el juego con la configuracion
	mainLoop();

	close();
	return 0;
}
