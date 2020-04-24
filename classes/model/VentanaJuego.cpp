//
// Created by rodrigosouto on 20/4/20.
//

#include "VentanaJuego.h"
#include "../Configuracion.h"
#include "../Log.h"

VentanaJuego::VentanaJuego(Configuracion* config, Jugador* jugador) {
	VentanaJuego::hud = new Hud();
	VentanaJuego::campo = crearCampo(config, jugador);
}

void VentanaJuego::crearEnemigos(int cantClase1, int cantClase2) {
	campo->crearNEnemigo2(cantClase2);
	campo->crearNEnemigo1(cantClase1);
}

void VentanaJuego::tick() {
	hud->tick();
	campo->tick();
}

Campo* VentanaJuego::crearCampo(Configuracion* config, Jugador* jugador){
	int inicioCampoEnEjeY = HUD_ALTO;
	Campo* campo = new Campo(jugador, config->getAnchoPantalla(), config->getAltoPantalla() - inicioCampoEnEjeY, inicioCampoEnEjeY);

	FondoVista* fondo;
	Json::Value fondosAPresentar = config->getRecursos("1");

	for(Json::Value f : fondosAPresentar) {
	    std::cout << f["archivo"].asString();
	    std::cout << f["velocidad"].asFloat();
		fondo = campo->nuevoFondo(f["archivo"].asString(), 0,0, f["velocidad"].asFloat());
	}

	l.info("Se creo correctamente el nivel 1 (Parallax)");
	return campo;
}
