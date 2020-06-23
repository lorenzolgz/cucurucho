#include "Hud.h"

#include <string>
#include "../../../commons/utils/Log.h"
#include "../../../commons/utils/Vector.h"


Hud::Hud() {
    posicion = Vector(0, 0);
	hi = new std::string;
	*hi = std::to_string(10000);

    l->info("Se creo correctamente el HUD.");
}

void Hud::tick() {
}

void Hud::actualizarHI(int posEnNivel) {
//	 *hi = to_string(posEnNivel);
}
