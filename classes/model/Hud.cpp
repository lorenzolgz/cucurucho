#include "Hud.h"
#include "../Utils.h"
#include "../Log.h"


Hud::Hud(SDL_Renderer *gRenderer) {
    posicion = Vector(0, 0);
    vista = new HudVista(gRenderer);
    l.info("Hud created");
}

void Hud::render() {
	vista->render(posicion);
}
