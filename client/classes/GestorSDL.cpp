#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL_render.h>
#include "GestorSDL.h"
#include "GraphicRenderer.h"
#include "../../commons/utils/Log.h"

bool GestorSDL::init(int anchoPantalla, int altoPantalla, ToastVista* toast) {
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
