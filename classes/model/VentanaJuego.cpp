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

void VentanaJuego::tick() {
	hud->tick();
	campo->tick();
}

Campo* VentanaJuego::crearCampo(Configuracion* config, Jugador* jugador){
	int inicioRectCampo = HUD_ALTO;
	SDL_Rect rectCampo = {0, inicioRectCampo, config->getAnchoPantalla(), config->getAltoPantalla() - inicioRectCampo };

	Campo* campo = new Campo(rectCampo, jugador);

	// Primer fondo se carga fuera del JSON
	int y_inicial = -24;
	FondoVista* fondo = campo->nuevoFondo("asteroids_0.png", 0, y_inicial, 9);

	// Resto de los fondos salen del JSON y se mapean
	Json::Value fondosAPresentar = config->getRecursos("1");
	for(Json::Value f : fondosAPresentar) {
		fondo = campo->nuevoFondo(f["archivo"].asString(), f["xOffset"].asFloat(),
								  fondo->getY() + fondo->getHeight(), f["velocidad"].asFloat());
	}

	campo->nuevoFondo("bg.png", 450, 0, 0.3);

	l.info("Parallax Stage 1 created");
	return campo;
}
