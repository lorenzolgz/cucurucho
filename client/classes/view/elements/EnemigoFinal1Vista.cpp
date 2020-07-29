#include "EnemigoFinal1Vista.h"
#include "../../GraphicRenderer.h"
#include "../../GeneradorDeTexturas.h"
#include "../../../../commons/utils/Vector.h"
#include "../Colores.h"
#include "../../../../commons/utils/Utils.h"
#include "ExplosionVista.h"


EnemigoFinal1Vista::EnemigoFinal1Vista() {
	this->gRenderer = GraphicRenderer::getInstance();
	GeneradorDeTexturas *generadorDeTexturas = GeneradorDeTexturas::getInstance();
	this->textura = generadorDeTexturas->generarTextura("boss.png");
	this->contador = 0;
	this->contadorMuerte = 0;
	this->ultimoEstado.clase = -1;

	this->audio = Audio::getInstance();
	this->audioExplosion = "sfx-14.wav";
	this->audio->generarEfecto(audioExplosion);

	l->info("La vista del Enemigo Final 1 fue creada correctamente.");
}

void EnemigoFinal1Vista::render(EstadoEnemigo estadoEnemigo, std::list<EstadoEnemigo> estadoExtensiones) {

	Vector posicion = Vector(estadoEnemigo.posicionX, estadoEnemigo.posicionY);
	SDL_Rect srcrect = {0, 0, ENEMIGO_FINAL1_SRC_ANCHO, ENEMIGO_FINAL1_SRC_ALTO};
	SDL_Rect dstrect = {(int) posicion.getX(), (int) posicion.getY(), ENEMIGO_FINAL1_SRC_ANCHO, ENEMIGO_FINAL1_SRC_ALTO};

	SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);

	renderGlow(srcrect, dstrect);

	contador++;
	ultimoEstado = estadoEnemigo;
	renderExtensiones(posicion, estadoExtensiones);
	l->debug("Vista del Enemigo Final 1: "+ posicion.getVector());
}

void EnemigoFinal1Vista::renderMuerte() {
	if (ultimoEstado.clase == -1) return;
	std::list<EstadoEnemigo> estadoExtensiones;
	Uint8 colorMod = contadorMuerte <= 200 ? contadorMuerte : 200;
	SDL_SetTextureColorMod(textura, 255 - colorMod, 255 - colorMod, 255 - colorMod);
	render(ultimoEstado, estadoExtensiones);
	contadorMuerte++;
	SDL_SetTextureAlphaMod(textura, 255);
}

void EnemigoFinal1Vista::renderExtensiones(Vector posicion, std::list<EstadoEnemigo> estadoExtensiones) {

	// Agregar a la estructura extensiones que falten
	for (int i = extensiones.size(); i < estadoExtensiones.size(); i++) {
		auto* ext = new EnemigoFinal1ExtVista();
		extensiones.push_back(ext);
	}

	Vector lock = posicion + Vector(ENEMIGO_FINAL1_SRC_ANCHO / 10, ENEMIGO_FINAL1_SRC_ALTO / 2);
	EstadoEnemigo estadoFueraCampo;
	estadoFueraCampo.posicionX = -100000;
	estadoFueraCampo.posicionY = -100000;
	estadoFueraCampo.energia = 0;

	for (EnemigoFinal1ExtVista* extension : extensiones) {
		bool destruida = true;
		// Al no mandar IDs, se identifican a las extensiones por distancia/rango
		auto it = estadoExtensiones.begin();
		while (it != estadoExtensiones.end()) {
			if (extension->estadoEnRango(*it)) {
				extension->render(*it, lock);
				estadoExtensiones.erase(it);
				destruida = false;
				break;
			}
			it++;
		}

		if (destruida) {
			extension->render(estadoFueraCampo, lock);
		}
	}
}


void EnemigoFinal1Vista::renderGlow(SDL_Rect srcrect, SDL_Rect dstrect) {

	std::array<int, 3> color = COLORES_VERDE.getColorGlow(contador / 4);
	Uint8 colorMod = contadorMuerte == 0;
	SDL_SetTextureColorMod(textura, color[0] * colorMod,
			color[1] * colorMod,
			color[2] * colorMod);

	srcrect.x += ENEMIGO_FINAL1_SRC_ANCHO;
	SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
	SDL_SetTextureColorMod(textura, 255, 255, 255);

}

ExplosionVista * EnemigoFinal1Vista::nuevaExplosionExt(Vector vector) {
	Vector offset = Vector(ENEMIGO_FINAL1_EXT_SRC_ANCHO / 2, ENEMIGO_FINAL1_EXT_SRC_ANCHO / 2);
	return new ExplosionVista(vector + offset, EXPLOSION_MEDIANA);
}

std::list<ExplosionVista*> EnemigoFinal1Vista::nuevasExplosiones(Vector vector) {
	audio->playEffect(audioExplosion);
	Vector offset = Vector(ENEMIGO_FINAL1_SRC_ANCHO / 2, ENEMIGO_FINAL1_SRC_ALTO / 2);
	std::list<ExplosionVista*> explosiones;

	explosiones.push_back(new ExplosionVista(vector + offset, EXPLOSION_GRANDE));

	for (int i = 0; i < 5; i++) {
		Vector randomPos = offset / 2 - Vector(rand() % (ENEMIGO_FINAL1_SRC_ANCHO / 3),
											   rand() % (ENEMIGO_FINAL1_SRC_ALTO / 3));
		explosiones.push_back(new ExplosionVista(vector + offset + randomPos, EXPLOSION_GRANDE, -6*i));
	}

	for (int i = 0; i < 5; i++) {
		Vector randomPos = offset / 2 - Vector(rand() % (ENEMIGO_FINAL1_SRC_ANCHO / 3),
											   rand() % (ENEMIGO_FINAL1_SRC_ALTO / 3));
		explosiones.push_back(new ExplosionVista(vector + offset + randomPos, EXPLOSION_GRANDE, -60 -i*15));
	}

	for (int i = 0; i < 15; i++) {
		Vector randomPos = offset - Vector(rand() % ENEMIGO_FINAL1_SRC_ANCHO,
								  rand() % ENEMIGO_FINAL1_SRC_ALTO);
		explosiones.push_back(new ExplosionVista(vector + offset + randomPos, EXPLOSION_MEDIANA,  -16*i));
	}
	return explosiones;
}
