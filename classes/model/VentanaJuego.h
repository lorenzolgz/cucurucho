//
// Created by javier on 9/4/20.
//

#ifndef CPP_SANDBOX_VENTANAJUEGO_H
#define CPP_SANDBOX_VENTANAJUEGO_H


#include <vector>
#include "../view/FondoVista.h"
#include "../view/VentanaJuegoVista.h"
#include <list>

class VentanaJuego {
public:
	VentanaJuego(SDL_Renderer* gRenderer, SDL_Rect rectVentana);
    FondoVista * nuevoFondo(const std::string &fileName, float xOffset, int yFondo, float modVelocidad);
    void render();

private:
	float velocidad;
	VentanaJuegoVista* vista;


    // Posicion X, para la logica del juego (no se usa aun)
    float posX;
};


#endif //CPP_SANDBOX_VENTANAJUEGO_H
