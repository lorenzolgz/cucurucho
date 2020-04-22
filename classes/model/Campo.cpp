//
// Created by javier on 9/4/20.
//

#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <string>
#include "Campo.h"
#include "Enemigo1.h"
#include "Enemigo2.h"

Campo::Campo(Jugador* jugador, int ancho, int alto, int inicioEnEjeY) {
	Campo::ancho = ancho;
	Campo::alto = alto;
	velocidad = 2;

	Campo::jugador = jugador;

	vista = new CampoVista(ancho, alto, inicioEnEjeY);
}

FondoVista * Campo::nuevoFondo(const std::string &fileName, float xOffset, int yFondo, float modVelocidad) {
	return vista->nuevoFondo(fileName, xOffset, yFondo, modVelocidad);
}

void Campo::crearNEnemigo1(int n) {
	std::srand(std::time(0)); //use current time as seed for random generator
	for (int i = 0; i < n; i++) {
		int posX = std::rand() % ancho;
		int posY = std::rand() % alto;
		Enemigo1* enemigo = new Enemigo1(posX, posY);
		// Esto se hace para que no queden parte fuera de la pantalla. Probablemente sólo para la primer entrega.
		if (!entidadEstaDentroDelCampo(enemigo, posX, posY)) {
			i--;
			continue;
		}

		enemigos.push_back(enemigo);
	}
}

void Campo::crearNEnemigo2(int n) {
	std::srand(std::time(0)); //use current time as seed for random generator
	for (int i = 0; i < n; i++) {
		int posX = std::rand() % ancho;
		int posY = std::rand() % alto;
		Enemigo2* enemigo = new Enemigo2(posX, posY);
		// Esto se hace para que no queden parte fuera de la pantalla. Probablemente sólo para la primer entrega.
		if (!entidadEstaDentroDelCampo(enemigo, posX, posY)) {
			i--;
			continue;
		}

		enemigos.push_back(enemigo);
	}
}

/*
 * Renderizar todos los fondos. A cada uno se le envia el renderer y ellos mismos
 * actualizan sus coordenadas en el campo.
 */
void Campo::tick() {
	vista->render(velocidad);
	std::for_each(enemigos.begin(), enemigos.end(), [](Ticker* t) { t->tick(); });
	jugador->tick();
}

bool Campo::entidadEstaDentroDelCampo(Entidad* entidad, int posX, int posY) {
	return (posX + entidad->getAncho() < ancho) && (posY + entidad->getAlto() < alto);
}
