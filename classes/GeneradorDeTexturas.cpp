//
// Created by ailen-magali on 19/4/20.
//

#include "GeneradorDeTexturas.h"

GeneradorDeTexturas::GeneradorDeTexturas(){

};

SDL_Texture* GeneradorDeTexturas::generarTextura(SDL_Renderer* gRenderer, string entidadDelJuego) {

    map<string, SDL_Texture*> texturas;

    texturas["Enemigo1"] = cargarTextura(gRenderer, "enemy01.png");
    texturas["Enemigo2"] = cargarTextura(gRenderer, "enemy02.png");
    texturas["Helper"] = cargarTextura(gRenderer, "helper.png");
    texturas["Hud"] = cargarTextura(gRenderer, "hud.png");
    texturas["Jugador"] = cargarTextura(gRenderer, "player.png");


    return texturas[entidadDelJuego];
};
