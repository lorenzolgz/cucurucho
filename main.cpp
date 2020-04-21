
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

Configuracion* leerJson(std::string ruta){
    Json::Value root;
    Json::Reader reader;
    std::ifstream file(ruta);
    file >> root;

    auto entriesArray = root["configuracion"]["niveles"]["1"];

    return new Configuracion(
            root["configuracion"]["resolucion"]["alto"].asInt64(),
            root["configuracion"]["resolucion"]["ancho"].asInt64(),
            root["configuracion"]["resolucion"]["escala"].asInt64(),
            root["configuracion"]["enemigos"]["tipoUno"].asInt64(),
            root["configuracion"]["enemigos"]["tipoDos"].asInt64(),
            root["configuracion"]["log"]["nivel"].asString(),
            root["configuracion"]["niveles"]);
}


void configurar(){
    try {
        config = leerJson("../config/config.json");
        l.setConf(config->getNivelLog());
    }
    catch (const std::exception& exc) {
        config = leerJson("../config/backup.json");
        l.setConf(config->getNivelLog());
        l.error(exc.what());
        l.debug("Ocurrió un problema al leer el archivo de configuración, se usará el de backup");
    }
    l.setConf(config->getNivelLog());
}


bool init(Configuracion* config) {
    int anchoPantalla = config->getAnchoPantalla();
    int altoPantalla = config->getAltoPantalla();
    int escalaPantalla = config->getEscalaPantalla();

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        l.error(("No se logro inicializar SDL! SDL_Error: %s\n", SDL_GetError()));
        return false;
    }

    // Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
    {
        l.debug("No se habilito el filro de la textura linear");
    }

    //Initialize SDL_image
    if (!(IMG_Init(IMG_INIT_PNG))) {
        l.error(("No se logro inicializar la SDL_image. SDL_image Error: %s\n", IMG_GetError()));
        return false;
    }

    gWindow = SDL_CreateWindow("cpp sandbox", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               anchoPantalla * escalaPantalla, altoPantalla * escalaPantalla, SDL_WINDOW_SHOWN);
    if (gWindow == nullptr) {
        l.error(("La Ventana no creo correctamente! SDL_Error: %s\n", SDL_GetError()));
        return false;
    }
    //Get window surface

    SDL_Renderer* gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == nullptr) {
        l.error(("El Renderer no se creo correctamente! SDL_Error: %s\n", SDL_GetError()));
        return false;
    }
    GraphicRenderer::setInstance(gRenderer);

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    SDL_RenderSetScale(gRenderer, escalaPantalla, escalaPantalla);

    l.info("La ventana se creo correctamente");
    return true;
}


void close(Configuracion* config) {
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

void mainLoop(Configuracion* config) {
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
    if (!init(config)) return 1;

    // Comienza el juego con la configuracion
    mainLoop(config);

    close(config);
    return 0;
}
