//
// Created by rodrigosouto on 20/4/20.
//

#ifndef CUCURUCHO_VENTANAJUEGO_H
#define CUCURUCHO_VENTANAJUEGO_H


#include "Hud.h"
#include "Campo.h"
#include "../Configuracion.h"

class VentanaJuego {
public:
	VentanaJuego(Configuracion* config, Jugador* jugador);
	void tick();

private:
	Hud *hud;
	Campo *campo;

	Campo *crearCampo(Configuracion *config, Jugador *jugador);
};


#endif //CUCURUCHO_VENTANAJUEGO_H
