//
// Created by javier on 24/4/20.
//

#include "TextoVista.h"
#include "../GeneradorDeTexturas.h"
#include <string>



TextoVista::TextoVista(std::string* nuevoTexto, struct TextoVistaParams params) {
	TextoVista::texto = nuevoTexto;
	TextoVista::posicion = params.posicion;
	TextoVista::color = params.color;
	TextoVista::alineacion = params.alineacion;
	TextoVista::textura = GeneradorDeTexturas::getInstance()->generarTextura("font.png");
	TextoVista::gRenderer = GraphicRenderer::getInstance();
	TextoVista::ancho = LETRA_ANCHO;
	TextoVista::alto = LETRA_ALTO;
	TextoVista::asciiOffset = ASCII_OFFSET;

	if (params.size == TEXTO_SIZE_SMALL) {
		setSmall();
	}
}

void TextoVista::renderLetra(char c, int pos, int size) {
	int posX = (int) posicion.getX() + pos * ancho;
	if (alineacion == ALINEACION_CENTRO) {
		posX -= (size * ancho) / 2 - ancho / 2;
	}
	SDL_Rect srcrect = {ancho * (c - asciiOffset), alto * color, ancho, alto};
	SDL_Rect dstrect = {posX, (int) posicion.getY(), ancho, alto};
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


void TextoVista::setSmall() {
	TextoVista::textura = GeneradorDeTexturas::getInstance()->generarTextura("font-small.png");
	TextoVista::ancho = LETRA_SMALL_ANCHO;
	TextoVista::alto = LETRA_SMALL_ALTO;
	TextoVista::asciiOffset = ASCII_SMALL_OFFSET;
}

void TextoVista::setTexto(const std::string texto) {
    *TextoVista::texto = texto;
}

void TextoVista::eRender(std::string texto, struct TextoVistaParams params) {
	auto* t = new TextoVista(&texto, params);
	t->render();
	delete t;
}

void TextoVista::setPosicion(Vector delta) {
    posicion = delta;
}

string *TextoVista::getTexto() const {
	return texto;
}
