//
// Created by camix on 4/5/20.
//

#ifndef CUCURUCHO_NIVELINTERMEDIOVISTA_H
#define CUCURUCHO_NIVELINTERMEDIOVISTA_H

#include <SDL_render.h>
#include "../../../commons/utils/Log.h"
#include "elements/FondoVista.h"
#include "elements/JugadorVista.h"
#include "CampoVista.h"

class NivelIntermedioVista {
public:
	NivelIntermedioVista(std::vector<JugadorVista*>* jugadores, int ancho, int alto);

	void renderNivelIntermedio(struct EstadoTick estadoTick);

	void renderEstadoLogin(EstadoLogin estadoLogin);

private:
	std::vector<JugadorVista*>* jugadores;
	SDL_Renderer *gRenderer;
	CampoVista* campoVista;
	EstadoTick estadoTick;
	int ancho;
    int alto;

	void renderEsperaJugador(JugadorVista* jugador, char* nombre, Vector offset, int colorTexto, int estaMuerto);

	void renderComun();

	void actualizarEstadoTick(struct EstadoTick tick);
};


#endif //CUCURUCHO_NIVELINTERMEDIOVISTA_H
