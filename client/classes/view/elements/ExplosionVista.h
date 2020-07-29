//
// Created by javier on 12/7/20.
//

#ifndef CUCURUCHO_EXPLOSIONVISTA_H
#define CUCURUCHO_EXPLOSIONVISTA_H


#include <SDL_render.h>
#include "../../../../commons/utils/Vector.h"
#include "../../Audio.h"

#define EXPLOSION_CHICA_SRC 30
#define EXPLOSION_MEDIANA_SRC 96
#define EXPLOSION_GRANDE_SRC 192

enum {
    EXPLOSION_CHICA,
    EXPLOSION_MEDIANA,
    EXPLOSION_GRANDE
};

class ExplosionVista {
public:
    ExplosionVista(Vector centro, int tipo, int contador = 0);

    bool activa();
    void render();

private:
    void inicializarValores(Vector centro, std::string path, int size);
    Vector posicion;
    SDL_Texture* textura;
    int size;
    int contador;

    Audio *audio;
    std::string audio_explosion;
};


#endif //CUCURUCHO_EXPLOSIONVISTA_H
