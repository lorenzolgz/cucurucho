
#include <cstdlib>
#include <ctime>
#include <queue>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../classes/model/Jugador.h"
#include "../classes/model/Nivel.h"
#include "../classes/config/ConfiguracionParser.h"
#include "../classes/model/ManagerNiveles.h"
#include "../classes/model/Titulo.h"

#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "../commons/protocols/protocolo.h"
#include "../commons/connections/ConexionCliente.h"
#include "../commons/connections/IniciadorComunicacion.h"


#define BACKUP_CONFIG "../config/backup.json"

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

Configuracion* config;

Log* l;

// !!!!
// --------------
// BEGIN socket setup
int posJugadorX = 0;
int posJugadorY = 0;


int sendData(int* client_socket, struct Command* client_command) {

	int total_bytes_written = 0;
	int bytes_written = 0;
	int send_data_size = sizeof(struct Command);
	bool client_socket_still_open = true;

	while ((send_data_size > total_bytes_written) && client_socket_still_open) {
		bytes_written = send(*client_socket, (client_command + total_bytes_written),
							 (send_data_size - total_bytes_written), MSG_NOSIGNAL);

		if (bytes_written < 0) { // Error
			return bytes_written;
		} else if (bytes_written == 0) { // Socket closed
			client_socket_still_open = false;
		} else {
			total_bytes_written += bytes_written;
		}
	}

	return 0;
}

int receiveData(int* client_socket, struct View* client_view) {

	int total_bytes_receive = 0;
	int bytes_receive = 0;
	int receive_data_size = sizeof(struct View);
	bool client_socket_still_open = true;

	while ((receive_data_size > bytes_receive) && client_socket_still_open) {
		bytes_receive = recv(*client_socket, (client_view + total_bytes_receive),
							 (receive_data_size - total_bytes_receive), MSG_NOSIGNAL);

		if (bytes_receive < 0) { // Error
			return bytes_receive;
		} else if (bytes_receive == 0) { // Socket closed
			client_socket_still_open = false;
		} else {
			total_bytes_receive += bytes_receive;
		}
	}

	return 0;
}

// END socket setup
// --------------


void configurar(string archivoConfig, string nivelLog) {
	ConfiguracionParser configuracionParser;
    l = new Log("client");
	try {
		config = configuracionParser.parsearConfiguracion(archivoConfig);
	}
	catch (const std::exception& exc) {
        // Primero aviso que no se pudo usar el original antes de seguir con el backup
	    l->error("Ocurrió un error al leer el archivo de configuración, se usará el de backup");

        // Solo se loguean las excepciones que tengan un what() para poder dar mas info
        if ((exc.what()!= NULL) && (exc.what()[0] == '\0')){
            l->error(exc.what());
        }
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

	if (nivelLog.empty()) {
	    nivelLog = config->getNivelLog();
	}
	l->setConf(nivelLog);

    l->info("Alto pantalla: " + std::to_string(config->getAltoPantalla()));
    l->info("Ancho pantalla: " + std::to_string(config->getAnchoPantalla()));
    l->info("Escala pantalla: " + std::to_string(config->getEscalaPantalla()));
    l->info("Nivel de Log: " + nivelLog);
}


bool init() {
	int anchoPantalla = config->getAnchoPantalla();
	int altoPantalla = config->getAltoPantalla();
	int escalaPantalla = config->getEscalaPantalla();

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


void closeSDL() {
	//Deallocate textures
	SDL_Renderer* gRenderer = GraphicRenderer::getInstance();
	SDL_DestroyRenderer(gRenderer);

	//Destroy window
	SDL_DestroyWindow(gWindow);

	//Free Configuration
	delete(config);

	l->info("Se libero toda la memoria");
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	l->info("La ventana se cerro correctamente");
}

void mainLoop() {
    int anchoPantalla = config->getAnchoPantalla();
	int altoPantalla = config->getAltoPantalla();
    bool quit = false;
    bool terminoNivelActual = false;
    SDL_Event e;
	Jugador* jugador = new Jugador(anchoPantalla / 8, altoPantalla / 2, COLORES_AZUL);
	ManagerNiveles* manager = new ManagerNiveles(config, jugador);
    Titulo* pantallaPrincipal = new Titulo(anchoPantalla, altoPantalla);

	l->info("Los objetos fueron inicializados correctamente a partir de los datos de la configuracion inicial");

	// !!!!
	//------------------------
	// BEGIN socket configuration
	struct View client_view;
	struct Command client_command;
	char* ip_address = "127.0.0.1";
	int port = 3040;

	//IniciadorComunicacion* iniciadorComunicacion =  new IniciadorComunicacion(ip_address, port);
	//ConexionCliente* conexionCliente = iniciadorComunicacion->conectar();
	// END socket configuration
	//------------------------

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
        // !!!! saque la pantalla de inicio
        /*
        bool onStart = currentKeyStates[SDL_SCANCODE_KP_ENTER] || currentKeyStates[SDL_SCANCODE_RETURN] || currentKeyStates[SDL_SCANCODE_SPACE];

        if (!pantallaPrincipal->isActivada(onStart)) {
            pantallaPrincipal->tick();
            SDL_RenderPresent(gRenderer);
            continue;
        }
         */


        /*
		// --------------------------
		// !!!!
		// BEGIN sockets messaging
		//keep communicating with server
		client_command.arriba = currentKeyStates[SDL_SCANCODE_UP];
		client_command.abajo = currentKeyStates[SDL_SCANCODE_DOWN];
		client_command.izquierda = currentKeyStates[SDL_SCANCODE_LEFT];
		client_command.derecha = currentKeyStates[SDL_SCANCODE_RIGHT];
		// Send data (command)
		conexionCliente->enviarMensaje(&client_command);
		printf("Send data: action = \n");
		//--------------------
		// Receive data (view)
		!!!! client_view = conexionCliente->recibirMensaje();
		printf("Incomming data: pos(X,Y) = (%d,%d)\n\n", client_view.positionX, client_view.positionY);
		posJugadorX = client_view.positionX;
		posJugadorY = client_view.positionY;
		// END sockets messaging
		// --------------------------
         */
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

    configurar(archivoConfig, nivelLog);

	// Inicializa SDL con la configuracion
	if (!init()) return 1;

	// Comienza el juego con la configuracion
	mainLoop();

	closeSDL();
	return 0;
}
