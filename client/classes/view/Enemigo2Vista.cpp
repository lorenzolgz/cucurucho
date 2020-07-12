#include "Enemigo2Vista.h"
#include <SDL_image.h>
#include "../../../commons/utils/Utils.h"
#include "../../../commons/utils/Log.h"
#include "../GeneradorDeTexturas.h"
#include "../GraphicRenderer.h"

Enemigo2Vista::Enemigo2Vista() {
	Enemigo2Vista::gRenderer = GraphicRenderer::getInstance();
    GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
    Enemigo2Vista::textura = generadorDeTexturas->generarTextura("enemy02.png");
    l->info("La vista del Enemigo 2 fue creada correctamente.");
}


void Enemigo2Vista::render(EstadoEnemigo estadoEnemigo) {
    Vector posicion = Vector(estadoEnemigo.posicionX, estadoEnemigo.posicionY);
	SDL_Rect srcrect = {0, 0 + ENEMIGO2_SRC_ALTO, ENEMIGO2_SRC_ANCHO, ENEMIGO2_SRC_ALTO};
	SDL_Rect dstrect = {(int) posicion.getX(), (int) posicion.getY(), ENEMIGO2_SRC_ANCHO, ENEMIGO2_SRC_ALTO};

	SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
	l->debug("Vista del Enemigo 02: "+ posicion.getVector());
}

ExplosionVista * Enemigo2Vista::nuevaExplosion(Vector vector) {
	Vector offset = Vector(ENEMIGO2_SRC_ANCHO / 2, ENEMIGO2_SRC_ALTO / 2);
	return new ExplosionVista(vector + offset, EXPLOSION_GRANDE);
}
