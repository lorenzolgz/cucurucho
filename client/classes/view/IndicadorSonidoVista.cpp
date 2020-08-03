//
// Created by javier on 3/8/20.
//

#include "IndicadorSonidoVista.h"
#include "../GraphicRenderer.h"
#include "../GeneradorDeTexturas.h"
#include "../../../commons/utils/Constantes.h"

IndicadorSonidoVista::IndicadorSonidoVista() {
	IndicadorSonidoVista::gRenderer = GraphicRenderer::getInstance();
	GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
	IndicadorSonidoVista::textura = generadorDeTexturas->generarTextura("audioindicator.png");
	IndicadorSonidoVista::contador = 120;
}

void IndicadorSonidoVista::render() {
	if (contador > 120) return;

	SDL_Rect viewport = {0, 0, PANTALLA_ALTO, PANTALLA_ANCHO};
	SDL_RenderSetViewport(gRenderer, &viewport);

	SDL_SetTextureAlphaMod(textura, 255 - (contador > 90) * (contador - 90) * 255 / 30);
	SDL_Rect srcrect = {INDICADOR_ANCHO * !muteado, 0, INDICADOR_ANCHO, INDICADOR_ALTO};
	SDL_Rect dstrect = {INDICADOR_ANCHO / 3,HUD_ALTO / 2 - INDICADOR_ALTO / 2, INDICADOR_ANCHO, INDICADOR_ALTO};

	SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
	contador++;
}

void IndicadorSonidoVista::setMuteado(bool muteado) {
	IndicadorSonidoVista::muteado = muteado;
	IndicadorSonidoVista::contador = 0;
}
