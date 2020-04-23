//
// Created by ailen-magali on 19/4/20.
//

#include "GeneradorDeTexturas.h"


SDL_Texture * GeneradorDeTexturas::cargarTextura(SDL_Renderer* gRenderer, const std::string& path) {
    const std::string& SPRITES_LOCATION = "../assets/sprites/";

    SDL_Surface* loadedSurface = IMG_Load((SPRITES_LOCATION + path).c_str());
    if (loadedSurface == nullptr) {
        l.error(("Error al cargar la imagen %s! SDL_image Error: %s.\n", IMG_GetError()));
    }

    SDL_Texture * textura = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (textura == nullptr) {
        l.error(("Error al cargar la textura de %s! SDL Error: %s.\n", SDL_GetError()));
    }

    SDL_FreeSurface(loadedSurface);
    return textura;
}


GeneradorDeTexturas* GeneradorDeTexturas::instance=NULL;

GeneradorDeTexturas* GeneradorDeTexturas::getInstance(){
    if (instance==NULL)
        instance = new GeneradorDeTexturas();
    else
        l.info("Creando instancia");

    return instance;
}

GeneradorDeTexturas::GeneradorDeTexturas(){
    l.info("Creacion de singleton");
}

SDL_Texture* GeneradorDeTexturas::generarTextura(string entidadDelJuego) {

    SDL_Renderer* gRenderer = GraphicRenderer::getInstance();
    SDL_Texture* textura = texturas[entidadDelJuego];

    if(textura==NULL){
        texturas[entidadDelJuego] = cargarTextura(gRenderer, entidadDelJuego);
        textura = texturas[entidadDelJuego];
    }

    return textura;
}
