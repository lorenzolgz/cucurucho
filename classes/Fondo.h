//
// Created by javier on 9/4/20.
//

#ifndef CPP_SANDBOX_FONDO_H
#define CPP_SANDBOX_FONDO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>


class Fondo {
public:
    Fondo(SDL_Renderer* gRenderer, const std::string &fileName, float xOffset, int y, float modVelocidad);
    void render(SDL_Renderer *gRenderer, float d);
    int getY() const;
    int getWidth() const;
    int getHeight() const;

private:
    float x1;
    float x2;
    int y;
    float xOffset;
    float modVelocidad;
    int width;
    int height;
    SDL_Texture* textura;
};

#endif //CPP_SANDBOX_FONDO_H
