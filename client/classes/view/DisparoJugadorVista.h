//
// Created by javier on 6/7/20.
//

#ifndef CUCURUCHO_DISPAROJUGADORVISTA_H
#define CUCURUCHO_DISPAROJUGADORVISTA_H

#include <SDL_render.h>
#include "../../../commons/utils/Vector.h"
#include "../Audio.h"

#define DISPARO_JUGADOR_SRC_ANCHO 96
#define DISPARO_JUGADOR_SRC_ALTO 24
#define DISPARO_JUGADOR_SRC_ALTO_OFFSET 177


class DisparoJugadorVista {
public:
    DisparoJugadorVista();
    // TODO: En vez de Vector deberia recibir un tick o lo que sea
    // Deberia tener posicion y numero de jugador
    void render(Vector posicion, int nroJugador);

private:
    SDL_Renderer* gRenderer;
    SDL_Texture* textura;

    EfectoSonido *audioDisparo1;
    EfectoSonido *audioDisparo2;

};


#endif //CUCURUCHO_DISPAROJUGADORVISTA_H
