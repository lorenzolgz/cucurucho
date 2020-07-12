//
// Created by javier on 6/7/20.
//

#ifndef CUCURUCHO_DISPAROJUGADORVISTA_H
#define CUCURUCHO_DISPAROJUGADORVISTA_H

#include <SDL_render.h>
#include "../../../commons/utils/Vector.h"
#include "../Audio.h"
#include "../../../commons/protocols/protocolo.h"
#include "ExplosionVista.h"

#define DISPARO_JUGADOR_SRC_ANCHO 96
#define DISPARO_JUGADOR_SRC_ALTO 24
#define DISPARO_JUGADOR_SRC_ALTO_OFFSET 177


class DisparoJugadorVista {
public:
    DisparoJugadorVista();
	void render(EstadoDisparo disparo);
	ExplosionVista *nuevaExplosion(Vector vector);


private:
    SDL_Renderer* gRenderer;
    SDL_Texture* textura;

    EfectoSonido *audioDisparo1;
    EfectoSonido *audioDisparo2;
};


#endif //CUCURUCHO_DISPAROJUGADORVISTA_H
