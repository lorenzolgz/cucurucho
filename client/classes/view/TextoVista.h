//
// Created by javier on 24/4/20.
//

#ifndef CUCURUCHO_TEXTOVISTA_H
#define CUCURUCHO_TEXTOVISTA_H

#include <SDL_render.h>
#include "../../../commons/utils/Vector.h"

enum {
	TEXTO_NULO,
	TEXTO_COLOR_AZUL,
	TEXTO_COLOR_ROJO,
	TEXTO_COLOR_ROSA,
	TEXTO_COLOR_TURQUESA,
	TEXTO_COLOR_VERDE,
	TEXTO_COLOR_NARANJA
};

enum {
	TEXTO_SIZE_NORMAL,
	TEXTO_SIZE_SMALL
};

const int ALINEACION_IZQUIERDA = 1;
const int ALINEACION_DERECHA = 0;
const int ALINEACION_CENTRO = 2;

const int LETRA_ALTO = 24;
const int LETRA_ANCHO = 24;
const int ASCII_OFFSET = 30;

const int LETRA_SMALL_ALTO = 21;
const int LETRA_SMALL_ANCHO = 15;
const int ASCII_SMALL_OFFSET = 47;

struct TextoVistaParams {
	TextoVistaParams(): alineacion(ALINEACION_IZQUIERDA), color(TEXTO_COLOR_AZUL), size(TEXTO_SIZE_NORMAL) {}
	TextoVistaParams(Vector posicion, int color, int alineacion):
		posicion(posicion),
		alineacion(alineacion),
		color(color),
		size(TEXTO_SIZE_NORMAL) {};
	TextoVistaParams(Vector posicion, int color, int alineacion, int size):
			posicion(posicion),
			alineacion(alineacion),
			color(color),
			size(size) {};
	int color;
	int alineacion;
	int size;
	Vector posicion;
};


class TextoVista {
public:
	TextoVista(std::string* texto, struct TextoVistaParams params);
	static void eRender(std::string texto, struct TextoVistaParams params);
    void render();

    void setTexto(const std::string texto);
	void setPosicion(Vector posicion);
	void setSmall();

	std::string *getTexto() const;

private:
    std::string* texto;
    Vector posicion;
    int color;
    int alineacion;
	int ancho;
	int alto;
    int asciiOffset;
	SDL_Texture* textura;
    SDL_Renderer* gRenderer;

    void renderLetra(char c, int pos, int size);


};


#endif //CUCURUCHO_TEXTOVISTA_H
