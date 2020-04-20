//
// Created by ailen-magali on 19/4/20.
//

#include "GeneradorDeTexturas.h"
#include "GraphicRenderer.h"

GeneradorDeTexturas* GeneradorDeTexturas::instance=NULL;

GeneradorDeTexturas* GeneradorDeTexturas::getInstance(){
    if (instance==NULL)
        instance = new GeneradorDeTexturas();
    else
        cout << "Getting existing instance" << endl;

    return instance;
}

GeneradorDeTexturas::GeneradorDeTexturas(){
    cout << "Creating singleton" << endl;
}

SDL_Texture* GeneradorDeTexturas::generarTextura(string entidadDelJuego) {
	SDL_Renderer* gRenderer = GraphicRenderer::getInstance();
    map<string, SDL_Texture*> texturas;

    texturas["enemy01.png"] = cargarTextura(gRenderer, "enemy01.png");
    texturas["enemy02.png"] = cargarTextura(gRenderer, "enemy02.png");
    texturas["helper.png"] = cargarTextura(gRenderer, "helper.png");
    texturas["hud.png"] = cargarTextura(gRenderer, "hud.png");
    texturas["player.png"] = cargarTextura(gRenderer, "player.png");


    return texturas[entidadDelJuego];
}
