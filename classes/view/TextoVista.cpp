//
// Created by javier on 24/4/20.
//

#include "TextoVista.h"
#include "../GeneradorDeTexturas.h"
#include <string>

const int LETRA_ALTO = 24;
const int LETRA_ANCHO = 24;
const int ASCII_OFFSET = 32;


TextoVista::TextoVista(std::string* nuevoTexto, Vector posicion, const int color, int alineacion) {
	TextoVista::texto = nuevoTexto;
	TextoVista::posicion = posicion;
	TextoVista::color = color;
	TextoVista::alineacion = alineacion;
	TextoVista::textura = GeneradorDeTexturas::getInstance()->generarTextura("font.png");
	TextoVista::gRenderer = GraphicRenderer::getInstance();
}

void TextoVista::renderLetra(char c, int pos, int size) {
    int posX = (int) posicion.getX() + pos * LETRA_ANCHO;
    if (alineacion == ALINEACION_CENTRO) {
        posX -= (size * LETRA_ANCHO) / 2 - LETRA_ANCHO / 2;
    }
    SDL_Rect srcrect = {LETRA_ANCHO * (c - ASCII_OFFSET), LETRA_ALTO * color, LETRA_ALTO, LETRA_ANCHO};
    SDL_Rect dstrect = {posX, (int) posicion.getY(), LETRA_ANCHO, LETRA_ALTO};
    SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
}

void TextoVista::render() {
	if (alineacion != ALINEACION_DERECHA) {
        for (int i = 0; i < texto->size(); i++){
            renderLetra((*texto)[i], i, texto->size());
        }
    } else {
        for (int i = texto->size(); i > 0; i--){
            renderLetra((*texto)[i - 1], i - texto->size(), texto->size());
        }
    }
}

void TextoVista::setTexto(const std::string texto) {
    *TextoVista::texto = texto;
}

void TextoVista::eRender(std::string texto, Vector posicion, const int color, int alineacion) {
    auto* t = new TextoVista(&texto, posicion, color, alineacion);
    t->render();
    delete t;
}
