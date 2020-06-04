//
// Created by javier on 3/6/20.
//

#include "ToastVista.h"
#include "HudVista.h"
#include "../GraphicRenderer.h"

const int TOAST_VELOCIDAD = 6;
const int TOAST_TICKS = 15;

ToastVista::ToastVista() {
    contador = 0;
    tiempo = -1;
    posicionFinal = Vector(HUD_SRC_ANCHO / 2, 24);
}

void ToastVista::render() {
    if (contador > tiempo * 60) return;

    SDL_Rect rect = { (int) (posicion.getX()) - ((textoMaximo) * LETRA_ANCHO / 2), (int) posicion.getY() - LETRA_ALTO / 2,
                      ((textoMaximo + 1) * LETRA_ANCHO), (int) (textos.size() + 1) * LETRA_ALTO - 3 };
    SDL_RenderFillRect(GraphicRenderer::getInstance(), &rect);

    Vector velocidad = Vector(0, TOAST_VELOCIDAD);
    if (contador < TOAST_TICKS) {
        posicion = posicion + velocidad;
    } else if (contador + TOAST_TICKS >= tiempo * 60) {
        posicion = posicion + velocidad * -1;
    }
    for (int i = 0; i < textos.size(); i++) {
        textos[i]->setPosicion(posicion + Vector(0, i * LETRA_ALTO));
        textos[i]->render();
    }
    contador++;
}

void ToastVista::setTexto(std::string texto, int tiempo, int color) {
    textos.clear();

    size_t pos = 0;
    int n = 0;
    textoMaximo = 0;
    std::string* token;
    while ((pos = texto.find('\n')) != std::string::npos) {
        token = new std::string(texto.substr(0, pos));
        textos.push_back(new TextoVista(token, Vector(0, 0), color, ALINEACION_CENTRO));
        texto.erase(0, pos + 1);
        if (pos > textoMaximo) {
            textoMaximo = pos;
        }
        n++;
    }
    textos.push_back(new TextoVista(new std::string(texto), Vector(0, 0), color, ALINEACION_CENTRO));
    if (texto.size() > textoMaximo) {
        textoMaximo = texto.size();
    }

    ToastVista::tiempo = tiempo;
    contador = 0;
    posicion = posicionFinal - Vector(0, TOAST_VELOCIDAD * TOAST_TICKS);
}
