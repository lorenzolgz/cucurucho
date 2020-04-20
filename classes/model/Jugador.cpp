#include "Jugador.h"
#include "../Utils.h"
#include "../Log.h"


Jugador::Jugador(SDL_Renderer* gRenderer, int x, int y) {
	Jugador::velocidadEscalar = JUGADOR_VELOCIDAD_ESCALAR;
	Jugador::posicion = Vector(x, y);
	Jugador::velocidad = Vector(0, 0);
	Jugador::contadorVelocidadY = 0;

	Jugador::helperAbove = new Helper(gRenderer, this, Vector(JUGADOR_ANCHO / 2, -JUGADOR_ALTO));
	Jugador::helperBelow = new Helper(gRenderer, this, Vector(JUGADOR_ANCHO / 2, JUGADOR_ALTO * 2));

	Jugador::vista = new JugadorVista(gRenderer);
    l.info("Player created");
}

void Jugador::calcularVectorVelocidad(bool arriba, bool abajo, bool izquierda, bool derecha) {
    double vParcial = 0;

    if ((arriba || abajo) && (izquierda || derecha)) {
        vParcial = velocidadEscalar / sqrt(2);
    } else if (arriba || abajo || izquierda || derecha) {
        vParcial = velocidadEscalar;
    }

    double vx = 0, vy = 0;
    if (arriba) {
        vy = -vParcial;
        contadorVelocidadY += contadorVelocidadY < 14;
    } else if (abajo) {
        vy = vParcial;
        contadorVelocidadY -= contadorVelocidadY > -14;
    } else {
        contadorVelocidadY += (contadorVelocidadY < 0) - (contadorVelocidadY > 0);
    }

    if (izquierda) {
        vx = -vParcial;
    } else if (derecha) {
        vx = vParcial;
    }

    velocidad = Vector(vx, vy);
    posicion = posicion + velocidad;
}

void Jugador::tick() {
	helperAbove->tick();
	helperBelow->tick();
	vista->render(posicion, contadorVelocidadY);
}

const Vector &Jugador::getPosicion() const {
    return posicion;
}

const Vector Jugador::getVelocidad() const {
    return velocidad;
}

int Jugador::getContador() const {
    return vista->getContador();
}
