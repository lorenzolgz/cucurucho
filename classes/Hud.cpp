//
// Created by javier on 11/4/20.
//

#include <string>
#include <SDL_image.h>
#include "Hud.h"
#include "Utils.h"
#include "Log.h"


Hud::Hud(SDL_Renderer *gRenderer) {
    Hud::gRenderer = gRenderer;
    posHud = {0, 0, HUD_ANCHO, HUD_ALTO};

    textura = cargarTextura(gRenderer, "hud.png");
    l.info("Hud created");
}

void Hud::render() {
    SDL_RenderSetViewport(gRenderer, &posHud);

    SDL_Rect srcrect = {0, 0, HUD_ANCHO, HUD_ALTO};
    SDL_Rect dstrect = {0, 0, HUD_ANCHO, HUD_ALTO};
    SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
}
