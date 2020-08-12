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

	renderInfo(estadoTick, estadoLogin);

	if (toast != nullptr) {
		toast->render();
	}
}


void HudVista::renderInfo(EstadoTick estadoTick, EstadoLogin estadoLogin) {
	if (estadoLogin.cantidadJugadores == 0) {
		for (EstadoJugador estadoJugador : estadoTick.estadosJugadores) {
			if (strlen(estadoJugador.usuario) > 0) estadoLogin.cantidadJugadores++;
		}
	}

	Vector yOffset = Vector(0, LETRA_ALTO * 19 / 24);

	struct TextoVistaParams params = {yOffset + Vector(HUD_SRC_ANCHO / 25, 0),
			TEXTO_COLOR_NARANJA,
			ALINEACION_IZQUIERDA};
	TextoVista::eRender("VIDAS: ", params);
	params.posicion = params.posicion + Vector(0, LETRA_ALTO * 5 / 4);
	TextoVista::eRender("PUNTOS: ", params);

	for (int i = 0; i < estadoLogin.cantidadJugadores; i++) {
		Vector posicion = yOffset + Vector(HUD_SRC_ANCHO * (2 + i) / (4 + estadoLogin.cantidadJugadores / 2), 0);
		renderInfoJugadorVertical(estadoTick.estadosJugadores[i],
						  posicion,
						  i + 1,
						  estadoLogin.nroJugador == i + 1 && HUD_DISTINTO);
	}
}

void HudVista::renderInfoJugadorVertical(EstadoJugador estado, Vector posicion, int nroJugador, bool esCliente) {
	std::string vidas = " 0" + std::to_string(estado.cantidadVidas);
	std::string puntos = std::to_string(estado.puntos);

	struct TextoVistaParams params = {posicion, nroJugador, ALINEACION_DERECHA};
	std::string vidaString = {VIDA_NAVE_IZQ, VIDA_NAVE_DER, ' '};
	if (esCliente) vidaString = '>' + vidaString;
	TextoVista::eRender(vidaString, params);

	params = {posicion + Vector(0, LETRA_ALTO - LETRA_SMALL_ALTO) / 2,
		   TEXTO_COLOR_NARANJA, ALINEACION_IZQUIERDA, TEXTO_SIZE_SMALL};
	if (!esCliente) {
		params.color = TEXTO_COLOR_GRIS;
	}
	TextoVista::eRender(vidas, params);

	params.posicion = params.posicion + Vector(0, LETRA_ALTO * 5 / 4);
	params.alineacion = ALINEACION_CENTRO;
	TextoVista::eRender(puntos, params);
}

void HudVista::renderInfoLegacy(EstadoTick estadoTick, EstadoLogin estadoLogin) {
	if (estadoLogin.cantidadJugadores == 0) {
		for (EstadoJugador estadoJugador : estadoTick.estadosJugadores) {
			if (strlen(estadoJugador.usuario) > 0) estadoLogin.cantidadJugadores++;
		}
	}

	if (estadoLogin.cantidadJugadores > 2) {
		renderInfoSinNombres(estadoTick, estadoLogin);
	} else {
		renderInfoConNombres(estadoTick, estadoLogin);
	}
}


// Este deberia llamarse si hay solo uno o dos jugadores
void HudVista::renderInfoConNombres(EstadoTick estadoTick, EstadoLogin estadoLogin) {
	Vector yOffset;
	if (estadoLogin.cantidadJugadores <= 1) {
		yOffset = Vector(0, HUD_SRC_ALTO / 2 - LETRA_ANCHO / 2);
	} else {
		yOffset = Vector(0, HUD_SRC_ALTO / 6);
	}
	for (int i = 0; i < estadoLogin.cantidadJugadores; i++) {
		Vector posicion = yOffset + Vector(HUD_SRC_ANCHO * 3 / 7, LETRA_ALTO * 3 / 2 * i);
		renderInfoJugador(estadoTick.estadosJugadores[i],
				posicion,
				i + 1,
				false);

		posicion = posicion + Vector(HUD_SRC_ANCHO / 8, 0);
		struct TextoVistaParams params = {posicion, i + 1, ALINEACION_IZQUIERDA};
		TextoVista::eRender(std::string(estadoTick.estadosJugadores[i].usuario), params);
	}
}


// Este deberia llamarse si hay mas de dos jugadores
void HudVista::renderInfoSinNombres(EstadoTick estadoTick, EstadoLogin estadoLogin) {
	Vector yOffset = Vector(0, HUD_SRC_ALTO / 6);
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