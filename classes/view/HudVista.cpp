#include "HudVista.h"
#include "../Utils.h"
#include "../GeneradorDeTexturas.h"
#include "../GraphicRenderer.h"
#include "../model/Nivel.h"
#include <string>


HudVista::HudVista() {
	HudVista::gRenderer = GraphicRenderer::getInstance();
    GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
    HudVista::textura = generadorDeTexturas->generarTextura("hud.png");
}

void HudVista::render(Vector posicion) {
    SDL_Rect hudrect = {(PANTALLA_ANCHO - HUD_ANCHO) / 2, 0, HUD_SRC_ANCHO, HUD_SRC_ALTO};
	SDL_RenderSetViewport(gRenderer, &hudrect);

	SDL_Rect srcrect = {0, 0, HUD_SRC_ANCHO, HUD_SRC_ALTO};
	SDL_Rect dstrect = {0, 0, HUD_SRC_ANCHO, HUD_SRC_ALTO};
	SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);

    for (TextoVista* c : textos){
        c->render();
    }
}

void HudVista::nuevoTexto(std::string* texto, Vector posicion, int color, bool alineacionIzq) {
	textos.emplace_back(new TextoVista(texto, posicion, color, alineacionIzq));
}
