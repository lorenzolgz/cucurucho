//
// Created by javier on 24/4/20.
//

#include "TextoView.h"
#include "../GeneradorDeTexturas.h"
#include <string>

const int LETRA_ALTO = 24;
const int LETRA_ANCHO = 24;
const int ASCII_OFFSET = 32;


TextoView::TextoView(std::string &texto, Vector posicion, const int color, bool alineacionIzq) {
    TextoView::texto = texto;
    TextoView::posicion = posicion;
    TextoView::color = color;
    TextoView::alineacionIzq = alineacionIzq;
    TextoView::textura = GeneradorDeTexturas::getInstance()->generarTextura("font.png");
    TextoView::gRenderer = GraphicRenderer::getInstance();
}

void TextoView::renderLetra(char c, int pos) {
    SDL_Rect srcrect = {LETRA_ANCHO * (c - ASCII_OFFSET), LETRA_ALTO * color, LETRA_ALTO, LETRA_ANCHO};
    SDL_Rect dstrect = {(int) posicion.getX() + pos * LETRA_ANCHO, (int) posicion.getY(), LETRA_ANCHO, LETRA_ALTO};
    SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
}

void TextoView::render() {
    if (alineacionIzq) {
        for (int i = 0; i < texto.size(); i++){
            renderLetra(texto[i], i);
        }
    } else {
        for (int i = texto.size(); i > 0; i--){
            renderLetra(texto[i - 1], i - texto.size());
        }
    }
}
