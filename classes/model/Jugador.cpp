#include "Jugador.h"
#include "../../commons/utils/Utils.h"
#include "../../commons/utils/Log.h"
#include "CampoMovil.h"
#include "../../server/classes/model/Jugador.h"


Jugador::Jugador(ColoresJugador colores) {
	Jugador::helperAbove = new Helper(this, Vector(JUGADOR_ANCHO / 2, -JUGADOR_ALTO), colores);
	Jugador::helperBelow = new Helper(this, Vector(JUGADOR_ANCHO / 2, JUGADOR_ALTO * 2), colores);

    Jugador::vista = new JugadorVista(std::move(colores));
    l->info("Se creo correctamente el Jugador.");
}

void Jugador::tick() {
	helperAbove->tick();
	helperBelow->tick();
	Vector posicion = Vector(estado.posicionX, estado.posicionY);
	vista->render(posicion, estado.contadorVelocidadY);
    l->debug("Posicion del Jugador: "+ posicion.getVector());
}

int Jugador::getContador() const {
    return vista->getContador();
}

void Jugador::setEstado(struct EstadoJugador estado) {
	Jugador::estado = estado;
	helperAbove->setEstado(estado.helper1);
	helperBelow->setEstado(estado.helper2);
}
