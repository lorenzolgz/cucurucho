#include "Enemigo1Vista.h"
#include <SDL_image.h>
#include "../../../../commons/utils/Utils.h"
#include "../../../../commons/utils/Log.h"
#include "../../GeneradorDeTexturas.h"
#include "../../GraphicRenderer.h"

Enemigo1Vista::Enemigo1Vista() {
	Enemigo1Vista::gRenderer = GraphicRenderer::getInstance();
    GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
	Enemigo1Vista::textura = generadorDeTexturas->generarTextura("enemy01.png");
	l->info("La vista del Enemigo 1 fue creada correctamente.");
}

void Enemigo1Vista::render(EstadoEnemigo estadoEnemigo) {
    Vector posicion = Vector(estadoEnemigo.posicionX, estadoEnemigo.posicionY);
    int velocidadX = 2;
	SDL_Rect srcrect = {0 + ENEMIGO1_SRC_ANCHO * (velocidadX < 10) * (velocidadX > 5)
						+ ENEMIGO1_SRC_ANCHO * 2 * (velocidadX > 10) * (velocidadX < 15)
						+ ENEMIGO1_SRC_ANCHO * 3 * (velocidadX > 15),
						0 , ENEMIGO1_SRC_ANCHO, ENEMIGO1_SRC_ALTO};
	SDL_Rect dstrect = {(int) posicion.getX(), (int) posicion.getY(), ENEMIGO1_SRC_ANCHO, ENEMIGO1_SRC_ALTO};

	SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
}

ExplosionVista * Enemigo1Vista::nuevaExplosion(Vector vector) {
	Vector offset = Vector(ENEMIGO1_SRC_ANCHO / 2, ENEMIGO1_SRC_ALTO / 2);
	return new ExplosionVista(vector + offset, EXPLOSION_MEDIANA);
}
