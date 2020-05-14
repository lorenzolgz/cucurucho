#include "Hud.h"
#include <string>
#include "../Log.h"


Hud::Hud() {
    posicion = Vector(0, 0);
	hi = new std::string;
	*hi = to_string(10000);
	vista = crearVista();

    l.info("Se creo correctamente el HUD.");
}

HudVista* Hud::crearVista() {
	HudVista* nuevaVista = new HudVista();

	nuevaVista->nuevoTexto(std::string("HI"), Vector(24, 24), TEXTO_COLOR_ROJO, true);
	nuevaVista->nuevoTextoVariable(hi, Vector(240, 24), TEXTO_COLOR_ROJO, false);
	nuevaVista->nuevoTexto(std::string("00"), Vector(240, 48), TEXTO_COLOR_NARANJA, false);

	nuevaVista->nuevoTexto(std::string("MOV NORMAL"), Vector(312, 24), TEXTO_COLOR_AZUL, true);

	nuevaVista->nuevoTexto(std::string("GUN TWIN"), Vector(312, 48), TEXTO_COLOR_NARANJA, true);

	nuevaVista->nuevoTexto(std::string("SPEED"), Vector(624, 24), TEXTO_COLOR_AZUL, true);
	nuevaVista->nuevoTexto(std::string(">"), Vector(624, 48), TEXTO_COLOR_ROJO, true);

	nuevaVista->nuevoTexto(std::string("NORMAL"), Vector(792, 24), TEXTO_COLOR_AZUL, true);

	return nuevaVista;
}

void Hud::tick() {
	vista->render(posicion);
}

void Hud::actualizarHI(int posEnNivel) {
	// *hi = to_string(posEnNivel);
}
