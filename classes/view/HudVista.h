#ifndef CUCURUCHO_HUDVISTA_H
#define CUCURUCHO_HUDVISTA_H


#include <SDL_render.h>
#include <vector>
#include "../../commons/utils/Vector.h"
#include "TextoVista.h"

const int HUD_SRC_ANCHO = 960;
const int HUD_SRC_ALTO = 96;

class HudVista {
public:
	HudVista();
	void render(Vector posicion);
	void nuevoTexto(std::string* texto, Vector posicion, int color, bool alineacionIzq);

private:
	SDL_Renderer* gRenderer;
	SDL_Texture* textura;
	std::vector<TextoVista*> textos;
};


#endif //CUCURUCHO_HUDVISTA_H
