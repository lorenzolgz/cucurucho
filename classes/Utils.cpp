//
// Created by javier on 11/4/20.
//

#include <SDL_render.h>
#include <SDL_image.h>
#include "Utils.h"

#define PI 3.14159265358979323846


SDL_Texture * cargarTextura(SDL_Renderer* gRenderer, const std::string& path) {
    const std::string& SPRITES_LOCATION = "../assets/sprites/";

    SDL_Surface* loadedSurface = IMG_Load((SPRITES_LOCATION + path).c_str());
    if (loadedSurface == nullptr) {
        printf("Error al cargar la imagen %s! SDL_image Error: %s\n", (SPRITES_LOCATION + path).c_str(), IMG_GetError());
    }

    SDL_Texture * textura = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (textura == nullptr) {
        printf("Error al cargar la textura de %s! SDL Error: %s\n", (SPRITES_LOCATION + path).c_str(), SDL_GetError());
    }

    SDL_FreeSurface(loadedSurface);
    return textura;
}

double cos_d(double angulo_d) {
    return cos(to_r(angulo_d));
}


double sin_d(double angulo_d) {
    return sin(to_r(angulo_d));
}


double to_r(double angulo_d) {
    return angulo_d * PI / 180;
}


double to_d(double angulo_r) {
    return angulo_r / PI * 180;
}
