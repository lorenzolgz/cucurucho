//
// Created by javier on 6/7/20.
//

#ifndef CUCURUCHO_DISPAROENEMIGOVISTA_H
#define CUCURUCHO_DISPAROENEMIGOVISTA_H

#include <SDL_render.h>
#include "../../../../commons/utils/Vector.h"
#include "../../../../commons/protocols/protocolo.h"
#include "../../Audio.h"
#include "ExplosionVista.h"

#define DISPARO_ENEMIGO_SRC_ANCHO 18
#define DISPARO_ENEMIGO_SRC_ALTO 18
#define DISPARO_ENEMIGO_SRC_ALTO_OFFSET 159

class DisparoEnemigoVista {
public:
    DisparoEnemigoVista();
    // TODO: En vez de Vector deberia recibir un tick o lo que sea
    // Deberia tener solo posicion
    void render(EstadoDisparo estadoDisparo);
	ExplosionVista* nuevaExplosion(Vector pos);

private:
    SDL_Renderer* gRenderer;
    SDL_Texture* textura;
    Audio *audio;
    std::string audioExplosion;
};


#endif //CUCURUCHO_DISPAROENEMIGOVISTA_H
