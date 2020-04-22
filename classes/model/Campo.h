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
#include "Entidad.h"

class Campo {
public:
	Campo(Jugador* jugador, int ancho, int alto, int inicioEnEjeY);
    FondoVista * nuevoFondo(const std::string &fileName, float xOffset, int yFondo, float modVelocidad);
	void crearNEnemigo1(int n);
	void crearNEnemigo2(int n);
    void tick();

private:
	int ancho;
	int alto;
	float velocidad;

	Jugador* jugador;
	std::list<Ticker*> enemigos;

	CampoVista* vista;

	bool entidadEstaDentroDelCampo(Entidad* entidad, int posX, int posY);

    // Posicion X, para la logica del juego (no se usa aun)
    float posX;
};


#endif //CPP_SANDBOX_CAMPO_H
