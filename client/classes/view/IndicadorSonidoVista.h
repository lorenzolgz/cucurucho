//
// Created by javier on 3/8/20.
//

#ifndef CUCURUCHO_INDICADORSONIDOVISTA_H
#define CUCURUCHO_INDICADORSONIDOVISTA_H


#include <SDL_render.h>

#define INDICADOR_ANCHO 72
#define INDICADOR_ALTO 51

class IndicadorSonidoVista {
public:
	IndicadorSonidoVista();
	void render();

	void setMuteado(bool muteado);

private:
	SDL_Renderer* gRenderer;
	SDL_Texture* textura;
	int contador;
	bool muteado;
};


#endif //CUCURUCHO_INDICADORSONIDOVISTA_H
