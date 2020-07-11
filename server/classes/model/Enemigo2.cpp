#include "Enemigo2.h"
#include "../../../commons/utils/Utils.h"
#include "../../../commons/utils/Log.h"
#include "Nivel.h"

const int OFFSET_A = 600;
const int OFFSET_B = 1500;

#include "../../../commons/utils/Constantes.h"
#include "life/VidaEnemigo2.h"

Enemigo2::Enemigo2(float x,float y, float velocidadX) {
    if (random() % 2 == 0) {
        x = -x + PANTALLA_ANCHO - ENEMIGO2_ANCHO;
        velocidadX *= -1;
    }
	this->velocidadEscalar = 1;
	this->posicion = Vector(x, y);
	this->velocidadX = velocidadX;
	this->vida = new VidaEnemigo2();
	l->info("Se creo correctamente el Enemigo 02.");
}

int Enemigo2::getAncho() {
	return ENEMIGO2_ANCHO;
}

int Enemigo2::getAlto() {
	return ENEMIGO2_ALTO;
}

void Enemigo2::tick() {
	posicion = Vector(posicion.getX() - velocidadX, posicion.getY());
	l->debug("Posicion del Enemigo 02: "+ posicion.getVector());
}

void Enemigo2::recalcularPosicion() {
// Por si queremos mostrar como entra y sale en loop, moficando el sprite dependiendo
// si avanza o retrocede
//
    if (posicion.getX() > OFFSET_A and velocidadX) {
        posicion = posicion + Vector(-velocidadEscalar, 0);
        if (posicion.getX() <= OFFSET_A) velocidadX = false;
    } else{
        posicion = posicion + Vector(velocidadEscalar, 0);
        if (posicion.getX() >= OFFSET_B) velocidadX = true;
    }
}

Vector Enemigo2::getPosicion() {
	return posicion;
}

struct EstadoEnemigo Enemigo2::state() {
	struct EstadoEnemigo estado;
	estado.posicionX = posicion.getX();
	estado.posicionY = posicion.getY();
	estado.clase = 2;
	return estado;
}

int Enemigo2::getTipoEntidad() {
	return ENTIDAD_ENEMIGO2;
}

std::list<Forma> Enemigo2::getFormas() {
	std::list<Forma> formas;
	Forma formaSimple = Forma(getPosicion().getX(), getPosicion().getY(), getAncho()-20, getAlto());
	formas.emplace_back(formaSimple);
	return formas;
}

VidaEntidad* Enemigo2::getVidaEntidad() {
	return vida;
}

void Enemigo2::aproximarAJugador(std::map<int, Jugador *> jugadores){
    Vector desplazamiento = jugadores.at(0)->getPosicion() - this->getPosicion();
    float desplazamientoHor = desplazamiento.getX();
    float desplazamientoVer = desplazamiento.getY();
    float distanciaMinima = desplazamiento.modulo();
    bool jugadorPorDerecha;
    bool jugadorPorArriba;

    desplazamientoHor < 0 ? jugadorPorDerecha = true : jugadorPorDerecha = false;
    desplazamientoVer < 0 ? jugadorPorArriba = true : jugadorPorArriba = false;

    std::map<int, Jugador *>::iterator it;
    for (it = jugadores.begin(); it != jugadores.end(); it++) {
        desplazamiento = it->second->getPosicion() - this->getPosicion();
        desplazamientoHor = desplazamiento.getX();
        desplazamientoVer = desplazamiento.getY();
        float distancia = desplazamiento.modulo();
        if(distancia < distanciaMinima){
            distanciaMinima = distancia;
            desplazamientoHor < 0 ? jugadorPorDerecha = true : jugadorPorDerecha = false;
            desplazamientoVer < 0 ? jugadorPorArriba = true : jugadorPorArriba = false;
        }
    }

    if((!jugadorPorDerecha && distanciaMinima <= DISTANCIA_ACTIVADORA_IA_2 && distanciaMinima > DISTANCIA_DESACTIVADORA_IA_IZQUIERDA_2) ||
       (jugadorPorDerecha && distanciaMinima <= DISTANCIA_ACTIVADORA_IA_2 && distanciaMinima > DISTANCIA_DESACTIVADORA_IA_DERECHA_2)) {

        float velocidadHorizontal = std::abs(velocidadX) * ATENUADOR_IA_2;
        float velocidadVertical = std::abs(velocidadX) * ATENUADOR_IA_2;

        if (jugadorPorDerecha)
            velocidadHorizontal = - velocidadHorizontal;

        if (jugadorPorArriba)
            velocidadVertical = - velocidadVertical;

        posicion = Vector(posicion.getX() + velocidadHorizontal, posicion.getY() + velocidadVertical);
        l->debug("Posicion del Enemigo 02: "+ posicion.getVector());

    } else if (distanciaMinima > DISTANCIA_ACTIVADORA_IA_2) {
        // Si ya se alejo lo suficiente tickeo como venia hasta encontrar otro jugador
        tick();
    }

}