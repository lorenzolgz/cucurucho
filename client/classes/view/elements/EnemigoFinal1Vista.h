#ifndef CUCURUCHO_ENEMIGOFINAL1VISTA_H
#define CUCURUCHO_ENEMIGOFINAL1VISTA_H


#include <SDL_render.h>
#include "../../../../commons/protocols/protocolo.h"
#include "EnemigoFinal1ExtVista.h"
#include "ExplosionVista.h"

const int ENEMIGO_FINAL1_SRC_ANCHO = 375;
const int ENEMIGO_FINAL1_SRC_ALTO = 288;

class EnemigoFinal1Vista {
public:
	EnemigoFinal1Vista();
	void render(EstadoEnemigo estadoEnemigo, std::list<EstadoEnemigo> list);
	void renderMuerte();

	ExplosionVista* nuevaExplosionExt(Vector vector);
	std::list<ExplosionVista*> nuevasExplosiones(Vector vector);

private:
	SDL_Renderer* gRenderer;
	SDL_Texture* textura;
	int contador;
	int contadorMuerte;
	EstadoEnemigo ultimoEstado;
	std::deque<EnemigoFinal1ExtVista*> extensiones;

	void renderGlow(SDL_Rect srcrect, SDL_Rect dstrect);

	void renderExtensiones(Vector posicion, std::list<EstadoEnemigo> estadoExtensiones);
};


#endif //CUCURUCHO_ENEMIGOFINAL1VISTA_H
