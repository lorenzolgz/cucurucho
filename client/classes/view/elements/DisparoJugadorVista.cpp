//
// Created by javier on 6/7/20.
//

#include "DisparoJugadorVista.h"
#include "../../GraphicRenderer.h"
#include "../../GeneradorDeTexturas.h"
#include "../Colores.h"
#include "ExplosionVista.h"


DisparoJugadorVista::DisparoJugadorVista() {
    DisparoJugadorVista::gRenderer = GraphicRenderer::getInstance();
    GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
    DisparoJugadorVista::textura = generadorDeTexturas->generarTextura("fx.png");

//  USO EFECTOS DE SONIDO: Creo instancia de efecto que quiero y cuando la necesito audio->play(volumen)
    DisparoJugadorVista::audio = Audio::getInstance();
    DisparoJugadorVista::audiodisparo = "sfx-01.wav";
    DisparoJugadorVista::audioexplosion = "sfx-25.wav";

    audio->generarEfecto(audiodisparo);
    audio->generarEfecto(audioexplosion);


    l->info("La vista del disparo del jugador fue creada correctamente.");
}

void DisparoJugadorVista::render(EstadoDisparo disparo) {
    if (disparo.inicio + DISPARO_RANGO == disparo.posicionX){
        audio->playEffect(audiodisparo);
    }
    Vector posicion = Vector(disparo.posicionX, disparo.posicionY);

    SDL_Rect srcrect = {0, DISPARO_JUGADOR_SRC_ALTO_OFFSET, DISPARO_JUGADOR_SRC_ANCHO, DISPARO_JUGADOR_SRC_ALTO};
    SDL_Rect dstrect = {(int) posicion.getX(), (int) posicion.getY(), DISPARO_JUGADOR_SRC_ANCHO, DISPARO_JUGADOR_SRC_ALTO};


    int contador = (int) posicion.getX();
    std::array<int, 3> color = COLORES_JUGADOR_ARR[disparo.nroJugador].getColorGlow(contador / 3);
    SDL_SetTextureColorMod(textura, color[0], color[1], color[2]);

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (contador % 2 == 0) {
        flip = SDL_FLIP_VERTICAL;
    }
    SDL_RenderCopyEx(gRenderer, textura, &srcrect, &dstrect, 0, nullptr, flip);

    SDL_SetTextureColorMod(textura, 255, 255, 255);
    srcrect.x += DISPARO_JUGADOR_SRC_ANCHO;
    SDL_RenderCopyEx(gRenderer, textura, &srcrect, &dstrect, 0, nullptr, flip);
    l->debug("Vista del disparo del jugador: "+ posicion.getVector());
}

ExplosionVista * DisparoJugadorVista::nuevaExplosion(Vector vector) {

    audio->playEffect(audioexplosion);
    Vector offset = Vector(DISPARO_JUGADOR_SRC_ANCHO * 4 / 5, DISPARO_JUGADOR_SRC_ALTO / 2);
	return new ExplosionVista(vector + offset, EXPLOSION_CHICA);
}
