//
// Created by javier on 6/7/20.
//

#ifndef CUCURUCHO_DISPAROENEMIGOVISTA_H
#define CUCURUCHO_DISPAROENEMIGOVISTA_H

#include <SDL_render.h>
#include "../../../commons/utils/Vector.h"

#define DISPARO_ENEMIGO_SRC_ANCHO 16
#define DISPARO_ENEMIGO_SRC_ALTO 16
#define DISPARO_ENEMIGO_SRC_ALTO_OFFSET 161

class DisparoEnemigoVista {
public:
    DisparoEnemigoVista();
    // TODO: En vez de Vector deberia recibir un tick o lo que sea
    // Deberia tener solo posicion
    void render(Vector posicion);

private:
    SDL_Renderer* gRenderer;
    SDL_Texture* textura;
};


#endif //CUCURUCHO_DISPAROENEMIGOVISTA_H
