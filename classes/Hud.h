//
// Created by javier on 11/4/20.
//

#ifndef CPP_SANDBOX_HUD_H
#define CPP_SANDBOX_HUD_H


#include <SDL_render.h>

class Hud {
public:
    Hud(SDL_Renderer* gRenderer);
    void render();
private:
    SDL_Renderer* gRenderer;
    SDL_Texture* textura;
    SDL_Rect posHud;
};


#endif //CPP_SANDBOX_HUD_H
