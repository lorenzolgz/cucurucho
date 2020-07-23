//
// Created by javier on 12/7/20.
//

#include "ExplosionVista.h"
#include "../../GeneradorDeTexturas.h"

ExplosionVista::ExplosionVista(Vector centro, int tipo) {
    ExplosionVista::audio = Audio::getInstance();
    ExplosionVista::audio_explosion = "sfx-25.wav";
    switch (tipo) {
        case EXPLOSION_CHICA:
            inicializarValores(centro, "explosion-small.png", EXPLOSION_CHICA_SRC);

            return;
        case EXPLOSION_MEDIANA:
            inicializarValores(centro, "explosion-med.png", EXPLOSION_MEDIANA_SRC);
            ExplosionVista::audio_explosion = "sfx-25.wav";

            return;
        case EXPLOSION_GRANDE:
            inicializarValores(centro, "explosion-big.png", EXPLOSION_GRANDE_SRC);
            ExplosionVista::audio_explosion = "sfx-25.wav";

            return;
    }
    this->contador = 100;
}

void ExplosionVista::inicializarValores(Vector centro, std::string path, int tam) {
    this->posicion = centro - Vector(tam / 2, tam / 2);
    this->textura = GeneradorDeTexturas::getInstance()->generarTextura(path);
    this->size = tam;
    this->contador = 0;
    l->debug("Nueva explosion en " + this->posicion.getVector());
}

void ExplosionVista::render() {
    int frame = contador / 3;
    SDL_Rect srcrect = {frame * size, 0, size, size};
    SDL_Rect dstrect = {(int) posicion.getX(), (int) posicion.getY(), size, size};
    SDL_RenderCopy(GraphicRenderer::getInstance(), textura, &srcrect, &dstrect);
    contador++;
}

bool ExplosionVista::activa() {
    return contador <= 15;
}