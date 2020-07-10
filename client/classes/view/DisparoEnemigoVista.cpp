//
// Created by javier on 6/7/20.
//

#include "DisparoEnemigoVista.h"
#include "../GraphicRenderer.h"
#include "../GeneradorDeTexturas.h"


DisparoEnemigoVista::DisparoEnemigoVista() {
    DisparoEnemigoVista::gRenderer = GraphicRenderer::getInstance();
    GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
    DisparoEnemigoVista::textura = generadorDeTexturas->generarTextura("fx.png");

    Audio *audio1 = Audio::getInstante();
    DisparoEnemigoVista::audioDisparo = audio1->generarSoundEffect("sfx-10.wav");

    l->info("La vista del disparo fue creada correctamente.");
}

void DisparoEnemigoVista::render(Vector posicion) {
    SDL_Rect srcrect = {0, DISPARO_ENEMIGO_SRC_ALTO_OFFSET, DISPARO_ENEMIGO_SRC_ANCHO, DISPARO_ENEMIGO_SRC_ALTO};
    SDL_Rect dstrect = {(int) posicion.getX(), (int) posicion.getY(), DISPARO_ENEMIGO_SRC_ANCHO, DISPARO_ENEMIGO_SRC_ALTO};

    int contador = (int) posicion.getX();
    srcrect.x += DISPARO_ENEMIGO_SRC_ANCHO * (contador % 4);
    SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
//    audioDisparo->playSoundEffect(300);
    l->debug("Vista del disparo del enemigo: "+ posicion.getVector());
}
