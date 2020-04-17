

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "classes/VentanaJuego.h"
#include "classes/Jugador.h"
#include "classes/Hud.h"
#include "classes/Enemigo2.h"
#include "classes/Log.h"
#include "classes/Enemigo1.h"
#include <iostream>

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 672;
const int SCREEN_FPS = 60;


//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

//The window renderer
SDL_Renderer* gRenderer = nullptr;

Log l = Log();

bool init() {
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

    gWindow = SDL_CreateWindow("cpp sandbox", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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
    SDL_RenderSetScale(gRenderer, 3, 3);

    l.info("Window was successfully created");
    return true;
}


void close() {

    //Deallocate textures
    SDL_DestroyRenderer(gRenderer);

    //Destroy window
    SDL_DestroyWindow(gWindow);

    l.info("Memory released ( todo:( )");
    //Quit SDL subsystems
    IMG_Quit();
    SDL_Quit();
    l.info("Window was successfully closed");
}


VentanaJuego crearVentanaJuego() {
    SDL_Rect rect_ventana;
    rect_ventana.x = 0;
    rect_ventana.y = 32;
    rect_ventana.w = SCREEN_WIDTH;
    rect_ventana.h = SCREEN_HEIGHT - rect_ventana.y;

    VentanaJuego ventana(gRenderer, rect_ventana);

    int y_inicial = -8;
    Fondo* fondo = ventana.nuevoFondo("asteroids_0.png", 0, y_inicial, 3);
    fondo = ventana.nuevoFondo("asteroids_1.png", 0, fondo->getY() + fondo->getHeight(), 2.5);
    fondo = ventana.nuevoFondo("asteroids_2.png", 0, fondo->getY() + fondo->getHeight(), 2);
    fondo = ventana.nuevoFondo("asteroids_3.png", 0, fondo->getY() + fondo->getHeight(), 1.5);
    fondo = ventana.nuevoFondo("asteroids_4.png", 0, fondo->getY() + fondo->getHeight(), 1.25);
    fondo = ventana.nuevoFondo("asteroids_5.png", 0, fondo->getY() + fondo->getHeight(), 1);
    fondo = ventana.nuevoFondo("asteroids_6.png", 0, fondo->getY() + fondo->getHeight(), 0.75);
    fondo = ventana.nuevoFondo("asteroids_7.png", 0, fondo->getY() + fondo->getHeight(), 0.45);
    fondo = ventana.nuevoFondo("asteroids_8.png", 0, fondo->getY() + fondo->getHeight(), 0.25);
    fondo = ventana.nuevoFondo("asteroids_9.png", 0, fondo->getY() + fondo->getHeight(), 0.12);
    fondo = ventana.nuevoFondo("asteroids_9.png", 300, fondo->getY() + fondo->getHeight(), 0.15);
    fondo = ventana.nuevoFondo("asteroids_8.png", 300, fondo->getY() + fondo->getHeight(), 0.25);
    fondo = ventana.nuevoFondo("asteroids_7.png", 300, fondo->getY() + fondo->getHeight(), 0.45);
    fondo = ventana.nuevoFondo("asteroids_6.png", 300, fondo->getY() + fondo->getHeight(), 0.75);
    fondo = ventana.nuevoFondo("asteroids_5.png", 300, fondo->getY() + fondo->getHeight(), 1);
    fondo = ventana.nuevoFondo("asteroids_4.png", 300, fondo->getY() + fondo->getHeight(), 1.25);
    fondo = ventana.nuevoFondo("asteroids_3.png", 300, fondo->getY() + fondo->getHeight(), 1.5);
    fondo = ventana.nuevoFondo("asteroids_2.png", 300, fondo->getY() + fondo->getHeight(), 2);
    fondo = ventana.nuevoFondo("asteroids_1.png", 300, fondo->getY() + fondo->getHeight(), 2.5);
    fondo = ventana.nuevoFondo("asteroids_0.png", 300, fondo->getY() + fondo->getHeight(), 3);

    ventana.nuevoFondo("bg.png", 450, 0, 0.1);

    l.info("Parallax Stage 1 created");
    return ventana;
}


void mainLoop() {
    bool quit = false;
    SDL_Event e;


    // SDL_Renderer* gRenderer, std::string &file_name, int y, int xOffset, float modVelocidad
    VentanaJuego ventana = crearVentanaJuego();
    Jugador jugador = Jugador(gRenderer, 40, SCREEN_WIDTH / 6);
    Hud hud = Hud(gRenderer);
    Enemigo1 enemigo1 = Enemigo1(gRenderer, 250, 140);

    Enemigo2 enemigo2 = Enemigo2(gRenderer, 200, 15);
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
        jugador.render();
        enemigo1.render();
        enemigo2.render();
        hud.render();

        //Update screen
        SDL_RenderPresent(gRenderer);
    }
}


int main(int, char**) {
    if (!init()) return 1;

    mainLoop();
    close();
    return 0;
}