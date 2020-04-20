#include "HudVista.h"
#include "../Utils.h"
#include "../GeneradorDeTexturas.h"


HudVista::HudVista(SDL_Renderer *gRenderer) {
	HudVista::gRenderer = gRenderer;
	//textura = cargarTextura(gRenderer, "hud.png");
    GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
    HudVista::textura = generadorDeTexturas->generarTextura(gRenderer, "hud.png");
}

void HudVista::render(Vector posicion) {
	// why this render? !!!!
	SDL_Rect hudrect = {0, 0, HUD_SRC_ANCHO, HUD_SRC_ALTO};
	SDL_RenderSetViewport(gRenderer, &hudrect);

	SDL_Rect srcrect = {0, 0, HUD_SRC_ANCHO, HUD_SRC_ALTO};
	SDL_Rect dstrect = {0, 0, HUD_SRC_ANCHO, HUD_SRC_ALTO};
	SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
}
