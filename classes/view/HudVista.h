#ifndef CUCURUCHO_HUDVISTA_H
#define CUCURUCHO_HUDVISTA_H


#include <SDL_render.h>
#include <vector>
#include "../Vector.h"
#include "TextoView.h"

const int HUD_SRC_ANCHO = 960;
const int HUD_SRC_ALTO = 96;

class HudVista {
public:
	HudVista();
	void render(Vector posicion);
    void nuevoTexto(std::basic_string<char> texto, Vector posicion, int color, bool alineacionIzq);

private:
	SDL_Renderer* gRenderer;
	SDL_Texture* textura;
	std::vector<TextoView> textos;
};


#endif //CUCURUCHO_HUDVISTA_H
