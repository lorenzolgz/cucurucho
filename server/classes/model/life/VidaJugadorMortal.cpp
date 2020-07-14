#include "VidaJugadorMortal.h"

VidaJugadorMortal::VidaJugadorMortal(int energia) : VidaEntidad(energia) {
}

int VidaJugadorMortal::danioColisionDisparoEnemigo1() {
    return 15;
}

int VidaJugadorMortal::danioColisionDisparoEnemigo2() {
    return 25;
}