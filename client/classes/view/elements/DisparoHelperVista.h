//
// Created by javier on 16/7/20.
//

#ifndef CUCURUCHO_DISPAROHELPERVISTA_H
#define CUCURUCHO_DISPAROHELPERVISTA_H

#define DISPARO_HELPER_SRC_ANCHO 42
#define DISPARO_HELPER_SRC_ALTO 42
#define DISPARO_HELPER_SRC_ALTO_OFFSET 204

#include "../../../../commons/protocols/protocolo.h"
#include "ExplosionVista.h"
#include "../../EfectoSonido.h"

class DisparoHelperVista {
public:
	DisparoHelperVista();
	void render(EstadoDisparo disparo);
	ExplosionVista *nuevaExplosion(Vector vector);


private:
	SDL_Renderer* gRenderer;
	SDL_Texture* textura;
};


#endif //CUCURUCHO_DISPAROHELPERVISTA_H
