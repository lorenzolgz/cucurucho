#ifndef CUCURUCHO_CAMPOVISTA_H
#define CUCURUCHO_CAMPOVISTA_H


#include <list>
#include <vector>
#include "../view/FondoVista.h"

class CampoVista {
public:
	CampoVista(SDL_Renderer* gRenderer, SDL_Rect rectCampo);
	FondoVista * nuevoFondo(const std::string &fileName, float xOffset, int yFondo, float modVelocidad);
	void render(float velocidad);

private:
	SDL_Renderer* gRenderer;
	// Posicion del campo del juego en la pantalla principal
	SDL_Rect posCampo;
	std::list<FondoVista*> fondos;
};


#endif //CUCURUCHO_CAMPOVISTA_H
