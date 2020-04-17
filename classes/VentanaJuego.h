//
// Created by javier on 9/4/20.
//

#ifndef CPP_SANDBOX_VENTANAJUEGO_H
#define CPP_SANDBOX_VENTANAJUEGO_H


#include <vector>
#include "Fondo.h"
#include <list>

class VentanaJuego {
public:
    float velocidad;
    SDL_Renderer* gRenderer;
    VentanaJuego(SDL_Renderer* gRenderer, SDL_Rect rectVentana);
    Fondo * nuevoFondo(const std::string &fileName, float xOffset, int yFondo, float modVelocidad);
    void render();
private:
    std::list<Fondo*> fondos;

    // Posicion de la ventana del juego en la pantalla principal
    SDL_Rect posVentana;

    // Posicion X, para la logica del juego (no se usa aun)
    float posX;
};


#endif //CPP_SANDBOX_VENTANAJUEGO_H
