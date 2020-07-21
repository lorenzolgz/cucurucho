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

	int renderPosX = estadoEnemigo.posicionX;
	int renderPosY = estadoEnemigo.posicionY;

	int angulo_trunc = ((int) estadoEnemigo.anguloDir % 90) - 11;

	SDL_Rect srcrect = {ENEMIGO1_SRC_ANCHO * (angulo_trunc >= 11)
						  + ENEMIGO1_SRC_ANCHO * (angulo_trunc >= 33)
						  + ENEMIGO1_SRC_ANCHO * (angulo_trunc >= 56)
						  - ENEMIGO1_SRC_ANCHO * 3 * (angulo_trunc >= 78),
						  0, ENEMIGO1_SRC_ANCHO, ENEMIGO1_SRC_ALTO};
	SDL_Rect dstrect = {renderPosX,
						  renderPosY,
						  ENEMIGO1_SRC_ANCHO, ENEMIGO1_SRC_ALTO};

	SDL_RenderCopyEx(gRenderer, textura, &srcrect, &dstrect, -(int) (estadoEnemigo.anguloDir / 90) * 90, nullptr, SDL_FLIP_NONE);
}

ExplosionVista * Enemigo1Vista::nuevaExplosion(Vector vector) {
	Vector offset = Vector(ENEMIGO1_SRC_ANCHO / 2, ENEMIGO1_SRC_ALTO / 2);
	return new ExplosionVista(vector + offset, EXPLOSION_MEDIANA);
}
