//
// Created by javier on 12/4/20.
//

#include <iostream>
#include "Helper.h"
#include "../../commons/utils/Utils.h"

Helper::Helper(Jugador* jugador, Vector posRelativa, ColoresJugador colores) {
	Helper::vista = new HelperVista(jugador, colores);
	Helper::primeraVez = true;
}

void Helper::tick() {
	Vector posicion = Vector(estado.posicionX, estado.posicionY);
	if (primeraVez) {
		primeraVez = false;
		for (int i = 0; i < 19; i++) {
			recorrido.push_front(posicion);
		}
	} else {
		recorrido.pop_back();
		recorrido.push_front(posicion);
	}

	vista->render(posicion, estado.angulo, recorrido);
}

void Helper::setEstado(struct EstadoHelper estado) {
	Helper::estado = estado;
}
