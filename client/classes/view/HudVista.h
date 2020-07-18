#ifndef CUCURUCHO_HUDVISTA_H
#define CUCURUCHO_HUDVISTA_H


#include <SDL_render.h>
#include <vector>
#include "../../../commons/utils/Vector.h"
#include "TextoVista.h"
#include "ToastVista.h"

const int HUD_SRC_ANCHO = 960;
const int HUD_SRC_ALTO = 96;

class HudVista {
public:
	HudVista();
	void render(struct EstadoTick estadoTick, struct EstadoLogin estadoLogin, std::string username);
	void renderInfoJugador(struct EstadoJugador estado, Vector posicion, int nroJugador, bool esCliente);

private:
	SDL_Renderer* gRenderer;
	SDL_Texture* textura;
};

extern ToastVista* toast;

#endif //CUCURUCHO_HUDVISTA_H
