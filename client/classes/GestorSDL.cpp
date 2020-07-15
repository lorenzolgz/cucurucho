#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_render.h>
#include "GestorSDL.h"
#include "GraphicRenderer.h"
#include "../../commons/utils/Log.h"
#include "view/HudVista.h"
#include "../../commons/utils/Constantes.h"

class Node;

bool GestorSDL::init(int anchoPantalla, int altoPantalla) {
	int escalaPantalla = PANTALLA_ESCALA;
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

    //Initialize SDL_mixer
    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
    {
        printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
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

void GestorSDL::close() {
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

bool GestorSDL::event(std::string* inputText) {
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

bool GestorSDL::reproducirMusica(std::string stringAudio) {

    l->error("Reproduciendo audio " + stringAudio);
    Audio* audio = new Audio();
    Musica* musica = audio->generarMusica(stringAudio);
    musica->play(80);
}

void GestorSDL::mutear() {

//    musica->mutear();

}

