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
    posHud = {0, 0, 320, 40};

    textura = cargarTextura(gRenderer, "font.png");

    l.info("Hud created");
}

void Hud::render() {
    SDL_RenderSetViewport(gRenderer, &posHud);

    SDL_Rect srcrect = {0, 40, 320, 32};
    SDL_Rect dstrect = {0, 0, 320, 32};
    SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);

}
