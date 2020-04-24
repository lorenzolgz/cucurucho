
#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <jsoncpp/json/json.h>
#include "classes/model/Campo.h"
#include "classes/model/Jugador.h"
#include "classes/model/Hud.h"
#include "classes/model/Helper.h"
#include "classes/model/Enemigo2.h"
#include "classes/Log.h"
#include "classes/model/Enemigo1.h"
#include "classes/Configuracion.h"
#include "classes/model/VentanaJuego.h"
#include "classes/GraphicRenderer.h"

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

Configuracion* config;

Log l = Log();

std::string parsearNivelLog(Json::Value root) {
    try {
        std::string nivelLog = root["configuracion"]["log"]["nivel"].asString();
        if (nivelLog.compare("error") && nivelLog.compare("info") && nivelLog.compare("debug")){
            l.error("Se intento setear un nivel de log invalido");
            throw std::exception();
        }
        return nivelLog;
    }
    catch(const std::exception& exc) {
        l.error("Ocurrio un error al obtener el nivel de logging");
        throw exc;
    }
}


void parsearEnemigos(const Json::Value &root, int &cantEnemigosUno, int &cantEnemigosDos) {
    try {
        cantEnemigosUno = root["configuracion"]["enemigos"]["tipoUno"].asInt64();
        cantEnemigosDos = root["configuracion"]["enemigos"]["tipoDos"].asInt64();

        if (cantEnemigosUno < 0) {
            l.error("Intento setearse una cantidad de enemigos_uno negativa");
            throw std::exception();
        }
        if (cantEnemigosDos < 0) {
            l.error("Intento setearse una cantidad de enemigos_dos negativa");
            throw std::exception();
        }
    }
    catch(const std::exception& exc) {
        l.error("Ocurrio un error al obtener la cantidad de enemigos");
        throw exc;
    }
}

void parsearResolucion(const Json::Value &root, int &altoPantalla, int &anchoPantalla, int &escala) {
    try {
        altoPantalla = root["configuracion"]["resolucion"]["alto"].asInt64();
        anchoPantalla = root["configuracion"]["resolucion"]["ancho"].asInt64();
        escala = root["configuracion"]["resolucion"]["escala"].asInt64();
        if (altoPantalla < 100) {
            l.error("Intento setearse un alto de pantalla muy pequeño");
            throw std::exception();
        }
        if (anchoPantalla < 100){
            l.error("Intento setearse un ancho de pantalla muy pequeño");
            throw std::exception();
        }
        if (escala < 0){
            l.error("Intento setearse una escala de pantalla negativa");
            throw std::exception();
        }
    }
    catch(const std::exception& exc) {
        l.error("Ocurrio un error al cargar la resolucion de pantalla");
        throw exc;
    }
}

Configuracion* parsearConfiguracion(std::string rutaJsonConfig){
    Json::Value root;
    std::ifstream archivo(rutaJsonConfig);
    archivo >> root;

    Json::Value rootFondos;
    Json::Value entriesArray;
    std::string rutaCarpetaConfig = "../config/";

    try {
        std::string rutaFondos = rutaCarpetaConfig += root["configuracion"]["rutaFondos"].asString();
        std::ifstream archivo(rutaFondos);
        archivo >> rootFondos;
        entriesArray = rootFondos;
    } catch(const std::exception& exc){
        l.error("Ocurrio un error al obtener las rutas de las imagenes de fondo");
        throw exc;
    }

    int altoPantalla;
    int anchoPantalla;
    int escala;
    int cantEnemigosUno;
    int cantEnemigosDos;
    std::string nivelLog;

    parsearResolucion(root, altoPantalla, anchoPantalla, escala);
    parsearEnemigos(root, cantEnemigosUno, cantEnemigosDos);
    nivelLog = parsearNivelLog(root);

    return new Configuracion(altoPantalla, anchoPantalla, escala, cantEnemigosUno, cantEnemigosDos, nivelLog, entriesArray);
}




void configurar(){
    try {
        config = parsearConfiguracion("../config/config.json");
        l.setConf(config->getNivelLog());
    }
    catch (const std::exception& exc) {
        config = parsearConfiguracion("../config/backup.json");
        l.setConf(config->getNivelLog());
        // Solo se loguean las excepciones que tengan un what() para poder dar mas info
        if ((exc.what()!= NULL) && (exc.what()[0] == '\0')){
            l.error(exc.what());
        }
        l.debug("Ocurrió un error al leer el archivo de configuración, se usará el de backup");
    }
    l.setConf(config->getNivelLog());
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

    gWindow = SDL_CreateWindow("cpp sandbox", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
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

    l.info("Se libero toda la memoria ( todo:( )");
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    l.info("La ventana se cerro correctamente");
}

void mainLoop() {
    bool quit = false;
    SDL_Event e;

    int anchoPantalla = config->getAnchoPantalla();
	int altoPantalla = config->getAltoPantalla();

	Jugador* jugador = new Jugador(anchoPantalla / 8, altoPantalla / 2);
	VentanaJuego* ventanaJuego = new VentanaJuego(config, jugador);
	ventanaJuego->crearEnemigos(config->getEnemigosTipoUno(), config->getEnemigosTipoDos());

    l.info("Los objetos fueron inicializados correctamente a partir de los datos de la configuracion inicial");

    while (!quit) {
        //Handle events on queue
        while (SDL_PollEvent( &e ) != 0)
        {
            //User requests quit
            if (e.type == SDL_QUIT)
            {
                quit = true;
            }
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        jugador->calcularVectorVelocidad(currentKeyStates[SDL_SCANCODE_UP],
                                        currentKeyStates[SDL_SCANCODE_DOWN],
                                        currentKeyStates[SDL_SCANCODE_LEFT],
                                        currentKeyStates[SDL_SCANCODE_RIGHT]);

		SDL_Renderer* gRenderer = GraphicRenderer::getInstance();
		//Clear screen
        SDL_RenderClear(gRenderer);

        //Render texture to screen
        ventanaJuego->tick();

        //Update screen
        SDL_RenderPresent(gRenderer);
    }
}


int main(int, char**) {
    configurar();
    // Inicializa con la configuracion
    if (!init()) return 1;

    // Comienza el juego con la configuracion
    mainLoop();

    close();
    return 0;
}
