#ifndef CUCURUCHO_VENTANAJUEGOVISTA_H
#define CUCURUCHO_VENTANAJUEGOVISTA_H


#include <list>
#include <vector>
#include "../view/FondoVista.h"

class VentanaJuegoVista {
public:
	VentanaJuegoVista(SDL_Renderer* gRenderer, SDL_Rect rectVentana);
	FondoVista * nuevoFondo(const std::string &fileName, float xOffset, int yFondo, float modVelocidad);
	void render(float velocidad);

private:
	SDL_Renderer* gRenderer;
	// Posicion de la ventana del juego en la pantalla principal
	SDL_Rect posVentana;
	std::list<FondoVista*> fondos;
};


#endif //CUCURUCHO_VENTANAJUEGOVISTA_H
