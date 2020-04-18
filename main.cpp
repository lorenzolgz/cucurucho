
#include <iostream>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <jsoncpp/json/json.h>
#include "classes/VentanaJuego.h"
#include "classes/Jugador.h"
#include "classes/Hud.h"
#include "classes/Helper.h"
#include "classes/Enemigo2.h"
#include "classes/Log.h"
#include "classes/Enemigo1.h"
#include "classes/Configuracion.h"

//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

//The window renderer
SDL_Renderer* gRenderer = nullptr;

Log l = Log();


Configuracion* leerJson(){

    Json::Value root;
    Json::Reader reader;
    std::ifstream file("../config/config.json");
    file >> root;
    return new Configuracion(
            root["configuracion"]["resolucion"]["alto"].asInt64(),
            root["configuracion"]["resolucion"]["ancho"].asInt64(),
            root["configuracion"]["resolucion"]["escala"].asInt64(),
            root["configuracion"]["enemigos"]["tipoUno"].asInt64(),
            root["configuracion"]["enemigos"]["tipoDos"].asInt64(),
            root["configuracion"]["log"]["nivel"].asString());
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


VentanaJuego crearVentanaJuego(int altoPantalla, int anchoPantalla) {
    SDL_Rect rect_ventana;
    rect_ventana.x = 0;
    rect_ventana.y = HUD_ALTO;
    rect_ventana.w = anchoPantalla;
    rect_ventana.h = altoPantalla - rect_ventana.y;

    VentanaJuego ventana(gRenderer, rect_ventana);

    int y_inicial = -24;
    Fondo* fondo = ventana.nuevoFondo("asteroids_0.png", 0, y_inicial, 9);
    fondo = ventana.nuevoFondo("asteroids_1.png", 0, fondo->getY() + fondo->getHeight(), 7.5);
    fondo = ventana.nuevoFondo("asteroids_2.png", 0, fondo->getY() + fondo->getHeight(), 6);
    fondo = ventana.nuevoFondo("asteroids_3.png", 0, fondo->getY() + fondo->getHeight(), 4.5);
    fondo = ventana.nuevoFondo("asteroids_4.png", 0, fondo->getY() + fondo->getHeight(), 3.75);
    fondo = ventana.nuevoFondo("asteroids_5.png", 0, fondo->getY() + fondo->getHeight(), 3);
    fondo = ventana.nuevoFondo("asteroids_6.png", 0, fondo->getY() + fondo->getHeight(), 2.25);
    fondo = ventana.nuevoFondo("asteroids_7.png", 0, fondo->getY() + fondo->getHeight(), 1.35);
    fondo = ventana.nuevoFondo("asteroids_8.png", 0, fondo->getY() + fondo->getHeight(), 0.75);
    fondo = ventana.nuevoFondo("asteroids_9.png", 0, fondo->getY() + fondo->getHeight(), 0.36);
    fondo = ventana.nuevoFondo("asteroids_9.png", 900, fondo->getY() + fondo->getHeight(), 0.45);
    fondo = ventana.nuevoFondo("asteroids_8.png", 900, fondo->getY() + fondo->getHeight(), 0.75);
    fondo = ventana.nuevoFondo("asteroids_7.png", 900, fondo->getY() + fondo->getHeight(), 1.35);
    fondo = ventana.nuevoFondo("asteroids_6.png", 900, fondo->getY() + fondo->getHeight(), 2.25);
    fondo = ventana.nuevoFondo("asteroids_5.png", 900, fondo->getY() + fondo->getHeight(), 3);
    fondo = ventana.nuevoFondo("asteroids_4.png", 900, fondo->getY() + fondo->getHeight(), 3.75);
    fondo = ventana.nuevoFondo("asteroids_3.png", 900, fondo->getY() + fondo->getHeight(), 4.5);
    fondo = ventana.nuevoFondo("asteroids_2.png", 900, fondo->getY() + fondo->getHeight(), 6);
    fondo = ventana.nuevoFondo("asteroids_1.png", 900, fondo->getY() + fondo->getHeight(), 7.5);
    fondo = ventana.nuevoFondo("asteroids_0.png", 900, fondo->getY() + fondo->getHeight(), 9);

    ventana.nuevoFondo("bg.png", 450, 0, 0.3);

    l.info("Parallax Stage 1 created");
    return ventana;
}


void mainLoop(Configuracion* config) {
    bool quit = false;
    SDL_Event e;

    int altoPantalla = config->getAltoPantalla();
    int anchoPantalla = config->getAnchoPantalla();

    VentanaJuego ventana = crearVentanaJuego(altoPantalla, anchoPantalla);
    Jugador jugador = Jugador(gRenderer, anchoPantalla / 8, altoPantalla / 2);
    Helper helper = Helper(gRenderer, &jugador, Vector(JUGADOR_ANCHO / 2, -JUGADOR_ALTO));
    Helper helper2 = Helper(gRenderer, &jugador, Vector(JUGADOR_ANCHO / 2, JUGADOR_ALTO * 2));
    Hud hud = Hud(gRenderer);

    Enemigo1 enemigo1 = Enemigo1(gRenderer, 825, 420);
    Enemigo2 enemigo2 = Enemigo2(gRenderer, 600, 45);
    l.info("Objects are initialized according to the initial configuration");

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
        jugador.calcularVectorVelocidad(currentKeyStates[SDL_SCANCODE_UP],
                                        currentKeyStates[SDL_SCANCODE_DOWN],
                                        currentKeyStates[SDL_SCANCODE_LEFT],
                                        currentKeyStates[SDL_SCANCODE_RIGHT]);

        //Clear screen
        SDL_RenderClear(gRenderer);

        //Render texture to screen
        ventana.render();
        helper.render();
        helper2.render();
        jugador.render();
        enemigo1.render();
        enemigo2.render();
        hud.render();

        //Update screen
        SDL_RenderPresent(gRenderer);
    }
}


int main(int, char**) {

    // Agregar logica de error al no poder leer el JSON o que este sea invalido (TBD)
    Configuracion* config = leerJson();
        // CONCEPTO VALIDACION
        // if(!validarConfiguracion(config)){
        //  log.error("Configuracion invalida");
        //  config = configHardcodeadaValida;
        // }

    if (!init(config)) return 1;
    mainLoop(config);

    close(config);
    return 0;
}
