//
// Created by javier on 6/7/20.
//

#include "DisparoEnemigoVista.h"
#include "../../GraphicRenderer.h"
#include "../../GeneradorDeTexturas.h"


DisparoEnemigoVista::DisparoEnemigoVista() {
    DisparoEnemigoVista::gRenderer = GraphicRenderer::getInstance();
    GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
    DisparoEnemigoVista::textura = generadorDeTexturas->generarTextura("fx.png");

    DisparoEnemigoVista::audio = Audio::getInstance();
    DisparoEnemigoVista::audioExplosion = "sfx-36.wav";
    audio->generarEfecto(audioExplosion);

    l->info("La vista del disparo fue creada correctamente.");
}

void DisparoEnemigoVista::render(EstadoDisparo estadoDisparo) {

    SDL_Rect srcrect = {0, DISPARO_ENEMIGO_SRC_ALTO_OFFSET, DISPARO_ENEMIGO_SRC_ANCHO, DISPARO_ENEMIGO_SRC_ALTO};
    SDL_Rect dstrect = {(int) estadoDisparo.posicionX, (int) estadoDisparo.posicionY, DISPARO_ENEMIGO_SRC_ANCHO, DISPARO_ENEMIGO_SRC_ALTO};

    int contador = (int) estadoDisparo.posicionX;
    srcrect.x += DISPARO_ENEMIGO_SRC_ANCHO * (contador % 4);
    SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
    l->debug("Vista del disparo del enemigo: " + Vector(estadoDisparo.posicionX, estadoDisparo.posicionY).getVector());

}

ExplosionVista* DisparoEnemigoVista::nuevaExplosion(Vector pos) {

    audio->playEffect(audioExplosion);
	Vector offset = Vector(DISPARO_ENEMIGO_SRC_ALTO * 2, DISPARO_ENEMIGO_SRC_ANCHO / 2);
	return new ExplosionVista(pos + offset, EXPLOSION_CHICA, -1);
}
