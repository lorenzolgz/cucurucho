//
// Created by javier on 24/4/20.
//

#ifndef CUCURUCHO_TEXTOVIEW_H
#define CUCURUCHO_TEXTOVIEW_H

#include <SDL_render.h>
#include "../Vector.h"

const int TEXTO_COLOR_AZUL = 1;
const int TEXTO_COLOR_ROJO = 2;
const int TEXTO_COLOR_NARANJA = 3;
const int TEXTO_COLOR_VERDE = 4;

class TextoView {
public:
    TextoView(std::string& texto, Vector posicion, const int color, bool alineacionIzq);
    void render();
private:
    std::string texto;
    Vector posicion;
    int color;
    bool alineacionIzq;
    SDL_Texture* textura;
    SDL_Renderer* gRenderer;

    void renderLetra(char c, int pos);
};


#endif //CUCURUCHO_TEXTOVIEW_H
