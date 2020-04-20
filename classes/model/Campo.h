//
// Created by javier on 9/4/20.
//

#ifndef CPP_SANDBOX_CAMPO_H
#define CPP_SANDBOX_CAMPO_H


#include <vector>
#include "../view/FondoVista.h"
#include "../view/CampoVista.h"
#include "Jugador.h"
#include <list>
#include "Ticker.h"

class Campo {
public:
	Campo(SDL_Rect rectCampo, Jugador* jugador);
    FondoVista * nuevoFondo(const std::string &fileName, float xOffset, int yFondo, float modVelocidad);
    void tick();

private:
	float velocidad;

	Jugador* jugador;
	std::list<Ticker*> enemigos;

	CampoVista* vista;


    // Posicion X, para la logica del juego (no se usa aun)
    float posX;
};


#endif //CPP_SANDBOX_CAMPO_H
