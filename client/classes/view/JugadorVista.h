#ifndef CUCURUCHO_JUGADORVISTA_H
#define CUCURUCHO_JUGADORVISTA_H

#include <SDL_render.h>
#include <string>
#include "../../../commons/utils/Vector.h"
#include "Colores.h"
#include "HelperVista.h"
#include "../../../commons/protocols/protocolo.h"
#include "../Audio.h"


const int JUGADOR_SRC_ANCHO = 96;
const int JUGADOR_SRC_ALTO = 48;

class HelperVista;

class JugadorVista {
public:
    JugadorVista(ColoresJugador jugador);
//    void render(Vector posicion, Vector posHelper1, float argHelper1, Vector posHelper2, float argHelper2);
    void render(struct EstadoJugador estadoJugador);
	int getContador() const;

private:
	SDL_Renderer* gRenderer;
	SDL_Texture* textura;
	HelperVista* helperAbove;
	HelperVista* helperBelow;
	ColoresJugador colores = ColoresJugador({}, {});
	ColoresJugador coloresRender = COLORES_GRIS;
	int contador;
	Vector posicion;

	void colorGlow();
    void colorShip(SDL_Rect srcrect, SDL_Rect dstrect);

	void calcularVelocidadY(Vector nuevaPosicion);

    int contadorVelocidadY;

    EfectoSonido *audioPerder;
    EfectoSonido *audioRevivir;
};


#endif //CUCURUCHO_JUGADORVISTA_H
