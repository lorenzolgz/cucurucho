
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
#include "classes/GestorSDL.h"
#include "classes/HiloConexionCliente.h"
#include "../commons/Thread.h"

#define BACKUP_CONFIG "../config/backup.json"

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
            (*conexionCliente)->cerrar();
            *conexionCliente = iniciadorComunicacion->conectar();
        }
        SDL_RenderPresent(GraphicRenderer::getInstance());
        return true;
    }

    return false;
}


// Comunicacion con el cliente.
// Primero envia la secuencia de teclas presionada, y despues recibe informacion del conexionServidor
// Si `nuevoNivel` es true, debe recibir el nivel en vez de la informacion del escenario (!!)
ConexionCliente* conexionLoop(ConexionCliente* conexionCliente, const Uint8 *currentKeyStates) {

    struct Comando client_command = { false, false, false, false };

    client_command.arriba = currentKeyStates[SDL_SCANCODE_UP];
    client_command.abajo = currentKeyStates[SDL_SCANCODE_DOWN];
    client_command.izquierda = currentKeyStates[SDL_SCANCODE_LEFT];
    client_command.derecha = currentKeyStates[SDL_SCANCODE_RIGHT];

    // Send data (command)
    conexionCliente->enviarComando(&client_command);

    return conexionCliente;
}

// Renderiza el juego. Devuelve `false` si llego al nivel final (para salir del juego)
// TODO: Hardcodeadisimo. Cambiar.
bool renderLoop(ManagerVista* manager, struct EstadoTick estadoTick, struct InformacionNivel informacionNivel, ConexionCliente* conexionCliente) {

    bool quit = false;

    manager->setInformacionNivel(informacionNivel);
    //Render texture to screen
    manager->render(estadoTick);

    quit = quit || informacionNivel.numeroNivel > 3;
    SDL_RenderPresent(GraphicRenderer::getInstance());

    return quit;
}


// TODO: Clase Partida que se encargue de organizar la información
void setEstadoTick(struct EstadoTick *estadoTick, nlohmann::json mensaje) {
    estadoTick->nuevoNivel = mensaje["numeroNivel"];
    int i = 0;
    for (; i < MAX_JUGADORES; i++ ) {
        estadoTick->estadosJugadores[i].helper1.posicionX = mensaje["estadosJugadores"][i]["helper1"]["posicionX"];
        estadoTick->estadosJugadores[i].helper1.posicionY = mensaje["estadosJugadores"][i]["helper1"]["posicionY"];
        estadoTick->estadosJugadores[i].helper1.angulo = mensaje["estadosJugadores"][i]["helper1"]["angulo"];
        estadoTick->estadosJugadores[i].helper2.posicionX = mensaje["estadosJugadores"][i]["helper2"]["posicionX"];
        estadoTick->estadosJugadores[i].helper2.posicionY = mensaje["estadosJugadores"][i]["helper2"]["posicionY"];
        estadoTick->estadosJugadores[i].helper2.angulo = mensaje["estadosJugadores"][i]["helper2"]["angulo"];
        estadoTick->estadosJugadores[i].posicionX = mensaje["estadosJugadores"][i]["posicionX"];
        estadoTick->estadosJugadores[i].posicionY = mensaje["estadosJugadores"][i]["posicionY"];

    }
    int j = 0;
    for (; j < MAX_ENEMIGOS; j++ ){
        estadoTick->estadosEnemigos[j].posicionX = mensaje["estadosEnemigos"][j]["posicionX"];
        estadoTick->estadosEnemigos[j].posicionY = mensaje["estadosEnemigos"][j]["posicionY"];
        estadoTick->estadosEnemigos[j].clase = mensaje["estadosEnemigos"][j]["clase"];
    }
}

void setInformacionNivel(struct InformacionNivel *informacionNivel, nlohmann::json mensaje) {
    informacionNivel->numeroNivel = mensaje["numeroNivel"];
    informacionNivel->velocidad = mensaje["velocidad"];
    strcpy(informacionNivel->informacionFinNivel, std::string(mensaje["informacionFinNivel"]).c_str());
    for (int i = 0; i < MAX_FONDOS ; i++){
        informacionNivel->informacionFondo[i].pVelocidad = mensaje["informacionFondo"][i]["velocidad"];
        strcpy(informacionNivel->informacionFondo[i].pFondo, std::string(mensaje["informacionFondo"][i]["fondo"]).c_str());
    }
}



void mainLoop() {
    int anchoPantalla = PANTALLA_ANCHO;
	int altoPantalla = PANTALLA_ALTO;
    bool quit = false;

    ManagerVista* manager = new ManagerVista({}, 0, anchoPantalla, altoPantalla);
    Titulo* pantallaPrincipal = new Titulo(anchoPantalla, altoPantalla);

	//------------------------
	// BEGIN socket configuration
    struct EstadoTick estadoTick;
    struct InformacionNivel informacionNivel;

	char* ip_address = (char*) "127.0.0.1";
	int port = 3040;
    IniciadorComunicacion* iniciadorComunicacion = new IniciadorComunicacion(ip_address, port);
    ConexionCliente* conexionCliente = iniciadorComunicacion->conectar();
    auto* colaComandos = new ColaBloqueante<nlohmann::json>();
    auto* hiloConexionCliente = new HiloConexionCliente(conexionCliente,colaComandos);
    l->info("Los objetos fueron inicializados correctamente a partir de los datos de la configuracion inicial");

    hiloConexionCliente->start();

    while (!quit) {
        const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
        SDL_RenderClear(GraphicRenderer::getInstance());

        std::string inputText;
        quit = quit || eventLoop(&inputText);

        // TODO: Separar mejor el logueo conexion del logueo vista
        if (pantallaInicioLoop(iniciadorComunicacion, &conexionCliente, pantallaPrincipal, inputText, currentKeyStates)) {
            continue;
        }

        if (!colaComandos->empty()) {
        	// TODO no es mejor primero vaciar y despues imprimir?
            nlohmann::json instruccion = colaComandos->pop();
			l->error("!!!! mainpop " + instruccion.dump());
			if (instruccion["tipoMensaje"] == INFORMACION_NIVEL) setInformacionNivel(&informacionNivel, instruccion);
            else if (instruccion["tipoMensaje"] == ESTADO_TICK) setEstadoTick(&estadoTick, instruccion);
            while (colaComandos->size() > 5) colaComandos->pop();
        }

        if (!conexionLoop(conexionCliente, currentKeyStates)) {
            continue;
        }

        quit = quit || renderLoop(manager, estadoTick, informacionNivel, conexionCliente);
    }

    if (conexionCliente != nullptr) {
        conexionCliente->cerrar();
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

    GestorSDL* gestorSDL = new GestorSDL();

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
	if (!gestorSDL->init(PANTALLA_ANCHO, PANTALLA_ALTO)) return 1;

	// Comienza el juego con la configuracion
	mainLoop();

	gestorSDL->close();
	return 0;
}
