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
    posicionFinal = Vector(HUD_SRC_ANCHO / 2, LETRA_ANCHO);
}

void ToastVista::render() {
    if (contador > tiempo * 60) return;

    // Rectangulo para mostrar un cuadrado negro solo atras del texto
    // En este momento queda feo
//    SDL_Rect rect = { (int) (posicion.getX()) - ((textoMaximo) * LETRA_ANCHO / 2), (int) posicion.getY() - LETRA_ALTO / 2,
//                      ((textoMaximo + 1) * LETRA_ANCHO), (int) (textos.size() + 1) * LETRA_ALTO - 3 };

	// Rectangulo para mostrar un cuadrado negro sobre el largo del HUD
    SDL_Rect rect = { (int) LETRA_ANCHO, (int) posicion.getY() - LETRA_ALTO / 2,
                      HUD_SRC_ANCHO - LETRA_ANCHO * 2, 3 * LETRA_ALTO - 3 };
	SDL_SetRenderDrawColor(GraphicRenderer::getInstance(), 0, 0, 0, 255);
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

// OBS: "textos" es un arreglo porque el texto que recibe se puede separar por '\n'.
// Aunque ahora solo se pueda mostrar una linea sola, se deja la funcionalidad.
void ToastVista::setTexto(std::string texto, int tiempo, int color) {
	if (!textos.empty() && *(textos[0]->getTexto()) == texto) {
		return;
	}

    textos.clear();

    size_t pos = 0;
    int n = 0;
    struct TextoVistaParams textoParams = TextoVistaParams(Vector(0, 0), color, ALINEACION_CENTRO);
    textoMaximo = 0;
    std::string* token;
    while ((pos = texto.find('\n')) != std::string::npos) {
        token = new std::string(texto.substr(0, pos));
        textos.push_back(new TextoVista(token, textoParams));
        texto.erase(0, pos + 1);
        if (pos > textoMaximo) {
            textoMaximo = pos;
        }
        n++;
    }
    textos.push_back(new TextoVista(new std::string(texto), textoParams));
    if (texto.size() > textoMaximo) {
        textoMaximo = texto.size();
    }

    ToastVista::tiempo = tiempo;
    contador = 0;
    posicion = posicionFinal - Vector(0, TOAST_VELOCIDAD * TOAST_TICKS);
}
