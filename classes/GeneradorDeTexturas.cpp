//
// Created by ailen-magali on 19/4/20.
//

#include "GeneradorDeTexturas.h"
#include "GraphicRenderer.h"
#include "Log.h"

GeneradorDeTexturas* GeneradorDeTexturas::instance=NULL;

GeneradorDeTexturas* GeneradorDeTexturas::getInstance(){
    if (instance==NULL)
        instance = new GeneradorDeTexturas();
    else
        l.info("Creando instancia");

    return instance;
}

GeneradorDeTexturas::GeneradorDeTexturas(){
    l.info("Creacion de sinngleton");
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
