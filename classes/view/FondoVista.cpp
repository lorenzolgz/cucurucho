//
// Created by javier on 9/4/20.
//

#include "FondoVista.h"
#include "../GraphicRenderer.h"
#include "../GeneradorDeTexturas.h"
#include <iostream>


FondoVista::FondoVista(const std::string &fileName, float xOffset, int y, float modVelocidad, float* velocidadNivelX) {
	FondoVista::gRenderer = GraphicRenderer::getInstance();
    GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
	textura = generadorDeTexturas->generarTextura(fileName);

	// Busca el ancho y alto de la imagen cargada
    SDL_QueryTexture(textura, nullptr, nullptr, &width, &height);
	FondoVista::y = y;
	FondoVista::xOffset = xOffset;
	FondoVista::x1 = 0;
	FondoVista::x2 = (float) width;
	FondoVista::modVelocidad = modVelocidad;
	FondoVista::velocidadNivelX = velocidadNivelX;
}

FondoVista::FondoVista(const std::string &fileName, float xOffset, int y, float modVelocidad) :
    FondoVista(fileName, xOffset, y, modVelocidad, nullptr){
}


void FondoVista::render() {
    float velocidad;
    if (velocidadNivelX) {
        velocidad = modVelocidad * (*velocidadNivelX);
    } else {
        velocidad = 0;
    }
    SDL_Rect dstrect1 = calcularCoords(&x1, y, width, height, velocidad, xOffset);
    SDL_Rect dstrect2 = calcularCoords(&x2, y, width, height, velocidad, xOffset);
    SDL_RenderCopy(gRenderer, textura, nullptr, &dstrect1);
    SDL_RenderCopy(gRenderer, textura, nullptr, &dstrect2);
}

int FondoVista::getY() const {
    return y;
}

int FondoVista::getWidth() const {
    return width;
}

int FondoVista::getHeight() const {
    return height;
}

/*
 * Calcula las nuevas coordenadas del fondo. Si llegó al borde de la pantalla,
 * la envia nuevamente al otro lado.
 */
SDL_Rect FondoVista::calcularCoords(float* x, int y, int width, int height, float speed, float xOffset) {
	*x -= speed;
	if (*x + (float) width < xOffset) {
		*x += (float) width * 2;
	}

	if (*x - (float) width > xOffset) {
		*x -= (float) width * 2;
	}

	return { (int) *x - (int) xOffset, y, width, height };
}
