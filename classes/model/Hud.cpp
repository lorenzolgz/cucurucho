#include "Hud.h"
#include <string>
#include "../Log.h"


Hud::Hud() {
    posicion = Vector(0, 0);
    vista = new HudVista();

    vista->nuevoTexto(std::string("HI"), Vector(24, 24), TEXTO_COLOR_ROJO, true);
    vista->nuevoTexto(std::string("100000"), Vector(240, 24), TEXTO_COLOR_ROJO, false);
    vista->nuevoTexto(std::string("00"), Vector(240, 48), TEXTO_COLOR_NARANJA, false);

    vista->nuevoTexto(std::string("MOV NORMAL"), Vector(312, 24), TEXTO_COLOR_AZUL, true);
    vista->nuevoTexto(std::string("GUN TWIN"), Vector(312, 48), TEXTO_COLOR_NARANJA, true);

    vista->nuevoTexto(std::string("SPEED"), Vector(624, 24), TEXTO_COLOR_AZUL, true);
    vista->nuevoTexto(std::string(">"), Vector(624, 48), TEXTO_COLOR_ROJO, true);

    vista->nuevoTexto(std::string("NORMAL"), Vector(792, 24), TEXTO_COLOR_AZUL, true);

    l.info("Se creo correctamente el HUD.");
}

void Hud::tick() {
	vista->render(posicion);
}
