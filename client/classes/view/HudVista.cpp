#include "HudVista.h"
#include "../GeneradorDeTexturas.h"
#include "../GraphicRenderer.h"
#include "ManagerVista.h"
#include <string>
#include "../../../commons/utils/Constantes.h"

#define HUD_DISTINTO 1

const char VIDA_NAVE_IZQ = 30;
const char VIDA_NAVE_DER = 31;

HudVista::HudVista() {
	this->gRenderer = GraphicRenderer::getInstance();
    GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
    this->textura = generadorDeTexturas->generarTextura("hud.png");
}

void HudVista::render(EstadoTick estadoTick, EstadoLogin estadoLogin, std::string username) {
    SDL_Rect hudrect = {(PANTALLA_ANCHO - HUD_SRC_ANCHO) / 2, 0, HUD_SRC_ANCHO, HUD_SRC_ALTO};
	SDL_RenderSetViewport(gRenderer, &hudrect);

	SDL_Rect srcrect = {0, HUD_SRC_ALTO * (estadoLogin.nroJugador - 1) * HUD_DISTINTO + HUD_SRC_ALTO * !HUD_DISTINTO, HUD_SRC_ANCHO, HUD_SRC_ALTO};
	SDL_Rect dstrect = {0, 0, HUD_SRC_ANCHO, HUD_SRC_ALTO};
	SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);

	Vector yOffset;
	if (estadoLogin.cantidadJugadores <= 2) {
		yOffset = Vector(0, HUD_SRC_ALTO / 2 - LETRA_ANCHO / 2);
	} else {
		yOffset = Vector(0, HUD_SRC_ALTO / 6);
	}
	for (int i = 0; i < estadoLogin.cantidadJugadores; i++) {
		Vector posicion = yOffset + Vector(0, LETRA_ALTO * 3 / 2 * ((int) (i / 2)));
		if (i % 2 == 0) {
			posicion = posicion + Vector(HUD_SRC_ANCHO * 3 / 7, 0);
		} else {
			posicion = posicion + Vector(HUD_SRC_ANCHO * 5 / 6, 0);
		}
		renderInfoJugador(estadoTick.estadosJugadores[i],
				posicion,
				i + 1,
				estadoLogin.nroJugador == i + 1 && HUD_DISTINTO);
	}

    if (toast != nullptr) {
        toast->render();
    }
}


void HudVista::renderInfoJugador(struct EstadoJugador estado, Vector posicion, int nroJugador, bool esCliente) {
	std::string vidas = "0" + std::to_string(estado.cantidadVidas);
	std::string puntos = std::to_string(estado.puntos);
	std::string textoTotal = puntos + "    " + vidas;

	struct TextoVistaParams params = {posicion, TEXTO_COLOR_ROJO, ALINEACION_DERECHA};
	if (!esCliente) {
		params.color = TEXTO_COLOR_NARANJA;
	}
	TextoVista::eRender(puntos + std::string(textoTotal.size() - puntos.size(), ' '), params);

	params.color = nroJugador;
	TextoVista::eRender(std::string({VIDA_NAVE_IZQ, VIDA_NAVE_DER, ' '}) + std::string(vidas.size(), ' '), params);

	params.color = TEXTO_COLOR_NARANJA;
	TextoVista::eRender(vidas, params);
}