
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

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

//The window renderer
SDL_Renderer* gRenderer = nullptr;

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


bool init(Configuracion* config) {

    int anchoPantalla = config->getAnchoPantalla();
    int altoPantalla = config->getAltoPantalla();
    int escalaPantalla = config->getEscalaPantalla();

    //Initialize SDL
    if(SDL_Init( SDL_INIT_VIDEO ) < 0) {
        l.error(("SDL could not initialize! SDL_Error: %s\n", SDL_GetError()));
        return false;
    }

    // Set texture filtering to linear
    if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
    {
        l.warning( "Linear texture filtering not enabled!" );
    }

    //Initialize SDL_image
    if(!(IMG_Init(IMG_INIT_PNG))) {
        l.error(( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() ));
        return false;
    }

    gWindow = SDL_CreateWindow("cpp sandbox", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
            anchoPantalla * escalaPantalla, altoPantalla * escalaPantalla, SDL_WINDOW_SHOWN);
    if(gWindow == nullptr) {
        l.error(("Window could not be created! SDL_Error: %s\n", SDL_GetError()));
        return false;
    }
    //Get window surface

    gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (gRenderer == nullptr) {
        l.error(("Renderer could not be created! SDL_Error: %s\n", SDL_GetError()));
        return false;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
    SDL_RenderSetScale(gRenderer, escalaPantalla, escalaPantalla);

    l.info("Window was successfully created");
    return true;
}


void close(Configuracion* config) {

    //Deallocate textures
    SDL_DestroyRenderer(gRenderer);

    //Destroy window
    SDL_DestroyWindow(gWindow);

    //Free Configuration
    delete(config);

    l.info("Memory released ( todo:( )");
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    l.info("Window was successfully closed");
}


Campo* crearCampo(Configuracion* config, Jugador* jugador){

    int altoPantalla = config->getAltoPantalla();
    int anchoPantalla = config->getAnchoPantalla();

    int inicioRectCampo = HUD_ALTO;
    SDL_Rect rectCampo = {0, inicioRectCampo, anchoPantalla, altoPantalla - inicioRectCampo };

    Campo* campo = new Campo(gRenderer, rectCampo, jugador);

    // Primer fondo se carga fuera del JSON
    int y_inicial = -24;
    FondoVista* fondo = campo->nuevoFondo("asteroids_0.png", 0, y_inicial, 9);

    // Resto de los fondos salen del JSON y se mapean
    Json::Value fondosAPresentar = config->getRecursos("1");
    for(Json::Value f : fondosAPresentar) {
        fondo = campo->nuevoFondo(f["archivo"].asString(), f["xOffset"].asFloat(),
        		fondo->getY() + fondo->getHeight(), f["velocidad"].asFloat());
    }

    campo->nuevoFondo("bg.png", 450, 0, 0.3);

    l.info("Parallax Stage 1 created");
    return campo;
}


void mainLoop(Configuracion* config) {
    bool quit = false;
    SDL_Event e;

    int anchoPantalla = config->getAnchoPantalla();
	int altoPantalla = config->getAltoPantalla();

    //Prueba

    GeneradorDeTexturas generadorDeTexturas = GeneradorDeTexturas();

    Jugador* jugador = new Jugador(gRenderer, anchoPantalla / 8, altoPantalla / 2);
	Campo* campo = crearCampo(config, jugador);
    Hud hud = Hud(gRenderer);

    l.info("Objects are initialized according to the initial configuration");

    //FinPrueba

    while (!quit) {

        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }

        }
        const Uint8* currentKeyStates = SDL_GetKeyboardState( NULL );
        jugador->calcularVectorVelocidad(currentKeyStates[SDL_SCANCODE_UP],
                                        currentKeyStates[SDL_SCANCODE_DOWN],
                                        currentKeyStates[SDL_SCANCODE_LEFT],
                                        currentKeyStates[SDL_SCANCODE_RIGHT]);

        //Clear screen
        SDL_RenderClear(gRenderer);

        //Render texture to screen
		campo->tick();
		hud.tick();

        //Update screen
        SDL_RenderPresent(gRenderer);
    }
}


int main(int, char**) {

    Configuracion* config;

    try {
        config = leerJson("../config/config.json");
    }
    catch (const std::exception& exc) {
        l.error(exc.what());
        l.warning("Ocurrió un problema al leer el archivo de configuración, se usará el de backup");
        config = leerJson("../config/backup.json");
    }

    // Inicializa con la configuracion
    if (!init(config)) return 1;

    // Comienza el juego con la configuracion
    mainLoop(config);

    close(config);
    return 0;

}
