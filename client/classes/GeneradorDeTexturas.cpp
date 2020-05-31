//
// Created by ailen-magali on 19/4/20.
//

#include "GeneradorDeTexturas.h"


SDL_Texture * GeneradorDeTexturas::cargarTextura(SDL_Renderer* gRenderer, const std::string& path) {
    const std::string& SPRITES_LOCATION = "../assets/sprites/";

    SDL_Surface* loadedSurface = IMG_Load((SPRITES_LOCATION + path).c_str());
    if (loadedSurface == nullptr) {
        l->error(std::string("Error al cargar la imagen! SDL_image Error:") + IMG_GetError());
    }

    SDL_Texture * textura = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (textura == nullptr) {
        l->error(std::string("Error al crear la textura de la imagen! SDL_image Error:") + SDL_GetError());
    }

    SDL_FreeSurface(loadedSurface);
    return textura;
}


GeneradorDeTexturas* GeneradorDeTexturas::instance=NULL;

GeneradorDeTexturas* GeneradorDeTexturas::getInstance(){
    if (instance==NULL) {
		instance = new GeneradorDeTexturas();
		l->info("Creando instancia GeneradorDeTexturas");
	}

    return instance;
}

GeneradorDeTexturas::GeneradorDeTexturas(){
    textura_defecto = cargarTextura(GraphicRenderer::getInstance(), "default.png");
    l->info("Creacion de instancia GeneradorDeTexturas");
}

SDL_Texture* GeneradorDeTexturas::generarTextura(string entidadDelJuego) {
    SDL_Renderer* gRenderer = GraphicRenderer::getInstance();
    SDL_Texture* textura = texturas[entidadDelJuego];

    if (textura == NULL){
        texturas[entidadDelJuego] = cargarTextura(gRenderer, entidadDelJuego);
        textura = texturas[entidadDelJuego];
    }

    if (textura == NULL){
        return textura_defecto;
    }
    return textura;
}
