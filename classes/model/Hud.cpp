#include "Hud.h"
#include "../Utils.h"
#include "../Log.h"


Hud::Hud() {
    posicion = Vector(0, 0);
    vista = new HudVista();
    l.info("Hud created");
}

void Hud::tick() {
	vista->render(posicion);
}
