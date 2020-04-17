//
// Created by javier on 11/4/20.
//

#include <SDL_render.h>
#include <SDL_image.h>
#include "Utils.h"


SDL_Texture * cargarTextura(SDL_Renderer* gRenderer, const std::string& path) {

    const std::string& SPRITES_LOCATION = "../assets/sprites/";

    SDL_Surface* loadedSurface = IMG_Load((SPRITES_LOCATION + path).c_str());
    if (loadedSurface == nullptr) {
        printf( "Error al cargar la imagen %s! SDL_image Error: %s\n", (SPRITES_LOCATION + path).c_str(), IMG_GetError() );
    }

    SDL_Texture * textura = SDL_CreateTextureFromSurface(gRenderer, loadedSurface );
    if (textura == nullptr) {
        printf( "Error al cargar la textura de %s! SDL Error: %s\n", (SPRITES_LOCATION + path).c_str(), SDL_GetError() );
    }

    SDL_FreeSurface( loadedSurface );
    return textura;
}
