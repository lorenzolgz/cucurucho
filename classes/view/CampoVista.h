#ifndef CUCURUCHO_CAMPOVISTA_H
#define CUCURUCHO_CAMPOVISTA_H


#include <list>
#include <vector>
#include "../view/FondoVista.h"

class CampoVista {
public:
	CampoVista(int ancho, int alto, int inicioEnEjeY);
	FondoVista * nuevoFondo(const std::string &fileName, float xOffset, int yFondo, float modVelocidad, float *velocidadMovilX);
	void render();

private:
	SDL_Renderer* gRenderer;
	// Posicion del campo del juego en la pantalla principal
	SDL_Rect posCampo;
	std::list<FondoVista*> fondos;
};


#endif //CUCURUCHO_CAMPOVISTA_H
