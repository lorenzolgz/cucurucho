//
// Created by javier on 9/4/20.
//

#include "Fondo.h"
#include "Utils.h"


Fondo::Fondo(SDL_Renderer* gRenderer, const std::string &fileName, float xOffset, int y, float modVelocidad) {
    textura = cargarTextura(gRenderer, fileName);
    // Busca el ancho y alto de la imagen cargada
    SDL_QueryTexture(textura, nullptr, nullptr, &width, &height);
    Fondo::y = y;
    Fondo::xOffset = xOffset;
    Fondo::x1 = 0;
    Fondo::x2 = (float) width;
    Fondo::modVelocidad = modVelocidad;
}

/*
 * Calcula las nuevas coordenadas del fondo. Si llegó al borde de la pantalla,
 * la envia nuevamente al otro lado.
 */
SDL_Rect calcularCoords(float* x, int y, int width, int height, float speed, float x_offset) {
    *x -= speed;
    if (*x + (float) width < x_offset) {
        *x += (float) width * 2;
    }

    if (*x - (float) width > x_offset) {
        *x -= (float) width * 2;
    }

    SDL_Rect dstrect;
    dstrect.x = (int) *x - (int) x_offset;
    dstrect.y = y;
    dstrect.w = width;
    dstrect.h = height;

    return dstrect;
}

void Fondo::render(SDL_Renderer *gRenderer, float velocidad) {
    SDL_Rect dstrect1 = calcularCoords(&x1, y, width, height, modVelocidad * velocidad, xOffset);
    SDL_Rect dstrect2 = calcularCoords(&x2, y, width, height, modVelocidad * velocidad, xOffset);

    SDL_RenderCopy(gRenderer, textura, nullptr, &dstrect1);
    SDL_RenderCopy(gRenderer, textura, nullptr, &dstrect2);
}

int Fondo::getY() const {
    return y;
}

int Fondo::getWidth() const {
    return width;
}

int Fondo::getHeight() const {
    return height;
}
