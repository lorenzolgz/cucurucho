#include "Enemigo2Vista.h"
#include <SDL_image.h>
#include "../../../../commons/utils/Utils.h"
#include "../../../../commons/utils/Log.h"
#include "../../GeneradorDeTexturas.h"
#include "../../GraphicRenderer.h"

Enemigo2Vista::Enemigo2Vista() {

    Enemigo2Vista::gRenderer = GraphicRenderer::getInstance();
    GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
    Enemigo2Vista::textura = generadorDeTexturas->generarTextura("enemy03.png");

    Enemigo2Vista::audio = Audio::getInstance();
    Enemigo2Vista::audioExplosion = "sfx-12.wav";

    audio->generarEfecto(audioExplosion);

    l->info("La vista del Enemigo 2 fue creada correctamente.");

}


void Enemigo2Vista::render(EstadoEnemigo estadoEnemigo) {
    Vector posicion = Vector(estadoEnemigo.posicionX, estadoEnemigo.posicionY);

    int contador = (int) posicion.modulo() / 7;
    bool flip = contador % 10 >= 5;

    SDL_Rect srcrect;
    if (!flip) {
		srcrect = {(contador % 5) * ENEMIGO2_SRC_ANCHO, 0, ENEMIGO2_SRC_ANCHO, ENEMIGO2_SRC_ALTO};
    } else {
		srcrect = {(4 - contador % 5) * ENEMIGO2_SRC_ANCHO, 0, ENEMIGO2_SRC_ANCHO, ENEMIGO2_SRC_ALTO};
    }
	SDL_Rect dstrect = {(int) posicion.getX(), (int) posicion.getY(), ENEMIGO2_SRC_ANCHO, ENEMIGO2_SRC_ALTO};

	SDL_RenderCopyEx(gRenderer, textura, &srcrect, &dstrect, 0, nullptr, flip ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);
	l->debug("Vista del Enemigo 02: "+ posicion.getVector());
}

ExplosionVista * Enemigo2Vista::nuevaExplosion(Vector vector) {
    audio->playEffect(audioExplosion);
	Vector offset = Vector(ENEMIGO2_SRC_ANCHO / 2, ENEMIGO2_SRC_ALTO / 2);
	return new ExplosionVista(vector + offset, EXPLOSION_GRANDE);
}
