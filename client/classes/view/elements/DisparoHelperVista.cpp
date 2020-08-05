//
// Created by javier on 16/7/20.
//

#include "DisparoHelperVista.h"
#include "../../GraphicRenderer.h"
#include "../../GeneradorDeTexturas.h"
#include "../../Audio.h"
#include "DisparoJugadorVista.h"
#include "../Colores.h"

DisparoHelperVista::DisparoHelperVista() {
	DisparoHelperVista::gRenderer = GraphicRenderer::getInstance();
	GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
	DisparoHelperVista::textura = generadorDeTexturas->generarTextura("fx.png");


	l->info("La vista del disparo del jugador fue creada correctamente.");
}

void DisparoHelperVista::render(EstadoDisparo disparo) {
	Vector posicion = Vector(disparo.posicionX, disparo.posicionY);

	int angulo = disparo.nroJugador / 16;
	int angulo_trunc = ((int) angulo % 90) - 11;
	int src_x_offset = (angulo_trunc >= 11) + (angulo_trunc >= 33) + (angulo_trunc >= 56) - 3 * (angulo_trunc >= 78);

	SDL_Rect srcrect = {DISPARO_HELPER_SRC_ANCHO * src_x_offset * 2, DISPARO_HELPER_SRC_ALTO_OFFSET,
					 DISPARO_HELPER_SRC_ANCHO, DISPARO_HELPER_SRC_ALTO};
	SDL_Rect dstrect = {(int) posicion.getX(), (int) posicion.getY(), DISPARO_HELPER_SRC_ANCHO, DISPARO_HELPER_SRC_ALTO};


	int contador = (int) posicion.modulo();
	std::array<int, 3> color = COLORES_JUGADOR_ARR[(disparo.nroJugador & 3)].getColorGlow(contador / 3);
	SDL_SetTextureColorMod(textura, color[0], color[1], color[2]);

	SDL_RenderCopyEx(gRenderer, textura, &srcrect, &dstrect, -(int) (angulo / 90) * 90, nullptr, SDL_FLIP_NONE);

	SDL_SetTextureColorMod(textura, 255, 255, 255);
	srcrect.x += DISPARO_HELPER_SRC_ANCHO;
	SDL_RenderCopyEx(gRenderer, textura, &srcrect, &dstrect, -(int) (angulo / 90) * 90, nullptr, SDL_FLIP_NONE);
	l->debug("Vista del disparo del jugador: "+ posicion.getVector());
}

ExplosionVista * DisparoHelperVista::nuevaExplosion(Vector vector) {
	Vector offset = Vector(DISPARO_HELPER_SRC_ANCHO / 2, DISPARO_HELPER_SRC_ALTO / 2);
	return new ExplosionVista(vector + offset, EXPLOSION_CHICA);
}
