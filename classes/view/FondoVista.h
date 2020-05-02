//
// Created by javier on 9/4/20.
//

#ifndef CPP_SANDBOX_FONDO_H
#define CPP_SANDBOX_FONDO_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>


class FondoVista {
public:
    FondoVista(const std::string &fileName, float xOffset, int y, float modVelocidad, float* velocidadNivelX);
    void render();
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
    float* velocidadNivelX;
    SDL_Texture* textura;
	SDL_Renderer* gRenderer;

	SDL_Rect calcularCoords(float* x, int y, int width, int height, float speed, float xOffset);
};

#endif //CPP_SANDBOX_FONDO_H
