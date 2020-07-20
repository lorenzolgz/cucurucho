#include "EnemigoFinal1Vista.h"
#include "../../GraphicRenderer.h"
#include "../../GeneradorDeTexturas.h"
#include "../../../../commons/utils/Vector.h"
#include "../Colores.h"
#include "../../../../commons/utils/Utils.h"


EnemigoFinal1Vista::EnemigoFinal1Vista() {
	this->gRenderer = GraphicRenderer::getInstance();
	GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
	this->textura = generadorDeTexturas->generarTextura("boss.png");
	this->contador = 0;

	for (int i = 0; i < 2; i++) {
		auto* ext = new EnemigoFinal1ExtVista();
		extensiones.push_back(ext);
	}

	l->info("La vista del Enemigo Final 1 fue creada correctamente.");
}

void EnemigoFinal1Vista::render(EstadoEnemigo estadoEnemigo) {
	Vector posicion = Vector(estadoEnemigo.posicionX, estadoEnemigo.posicionY);
	SDL_Rect srcrect = {0, 0, ENEMIGO_FINAL1_SRC_ANCHO, ENEMIGO_FINAL1_SRC_ALTO};
	SDL_Rect dstrect = {(int) posicion.getX(), (int) posicion.getY(), ENEMIGO_FINAL1_SRC_ANCHO, ENEMIGO_FINAL1_SRC_ALTO};

	SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);

	renderGlow(srcrect, dstrect);

	renderExtensiones(estadoEnemigo, posicion);

	contador++;
	l->debug("Vista del Enemigo Final 1: "+ posicion.getVector());
}

void EnemigoFinal1Vista::renderExtensiones(EstadoEnemigo estadoEnemigo, Vector posicion) {
	int i = 0;
	for (EnemigoFinal1ExtVista* ext : extensiones) {
		Vector lock = posicion + Vector(ENEMIGO_FINAL1_SRC_ANCHO / 10, ENEMIGO_FINAL1_SRC_ALTO / 2);
		lock = lock + Vector(0, - ENEMIGO_FINAL1_EXT_SRC_ANCHO / 2 + (i == 0 ? ENEMIGO_FINAL1_SRC_ALTO / 8 : - ENEMIGO_FINAL1_SRC_ALTO / 8));

		EstadoEnemigo est;
		est.posicionX = lock.getX() - 250;
		est.posicionY = lock.getY() + 100 * (i == 0 ? - sin_d(contador * 3) : sin_d(contador * 3));
		ext->render(est, lock);
		i++;
	}
}


void EnemigoFinal1Vista::renderGlow(SDL_Rect srcrect, SDL_Rect dstrect) {

	std::array<int, 3> color = COLORES_VERDE.getColorGlow(contador / 4);
	SDL_SetTextureColorMod(textura, color[0], color[1], color[2]);

	srcrect.x += ENEMIGO_FINAL1_SRC_ANCHO;
	SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
	SDL_SetTextureColorMod(textura, 255, 255, 255);

}