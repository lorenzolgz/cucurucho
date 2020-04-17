//
// Created by javier on 12/4/20.
//

#include <iostream>
#include "Helper.h"
#include "Utils.h"


Helper::Helper(SDL_Renderer *gRenderer, Jugador* jugador, Vector posRelativa) {
    Helper::gRenderer = gRenderer;
    Helper::jugador = jugador;
    Helper::posRelativa = posRelativa;
    Helper::posicion = posRelativa + jugador->getPosicion();
    Helper::velocidad = Vector(0, 0);
    Helper::velAngular = HELPER_VEL_ANGULAR;
    Helper::aceleracion = HELPER_ACELERACION;
    Helper::angulo = 0;
    textura = cargarTextura(gRenderer, "helper.png");

    for (int i = 0; i < 19; i++) {
        recorrido.push_front(posicion);
    }
}

void Helper::renderGlow() {
    int contador = jugador->getContador();
    Uint8 COLORES[16][3] = {{206, 160, 239},
                            {173, 138, 239},
                            {140, 101, 239},
                            {99, 69, 239},
                            {66, 32, 239},
                            {33, 0, 206},
                            {33, 0, 173},
                            {0, 0, 140},
                            {0, 0, 99},
                            {0, 0, 140},
                            {33, 0, 173},
                            {33, 0, 206},
                            {66, 32, 239},
                            {99, 69, 239},
                            {140, 101, 239},
                            {173, 138, 239}};

    SDL_SetTextureColorMod(textura, COLORES[contador % 16][0], COLORES[contador % 16][1], COLORES[contador % 16][2]);

    SDL_Rect glowsrc = { 0, HELPER_ANCHO, HELPER_ALTO, HELPER_ANCHO};
    SDL_Rect glowdst = {(int) posicion.getX() - HELPER_RADIO_BALL,
                        (int) posicion.getY() - HELPER_RADIO_BALL,
                        HELPER_ALTO, HELPER_ANCHO};

    SDL_RenderCopy(gRenderer, textura, &glowsrc, &glowdst);


    if (contador % 6 < 3) {
        // Una de las tres posibles particulas [0, 1, 2]
        int glow = contador % 6;
        glowsrc = {HELPER_ANCHO * glow, HELPER_ALTO * 2, HELPER_ANCHO, HELPER_ALTO};
        glowdst = {(int) recorrido[6 * (glow + 1)].getX() - HELPER_RADIO_BALL,
                   (int) recorrido[6 * (glow + 1)].getY() - HELPER_RADIO_BALL,
                   HELPER_ANCHO, HELPER_ALTO };
        SDL_RenderCopy(gRenderer, textura, &glowsrc, &glowdst);
    }

    SDL_SetTextureColorMod(textura, 255, 255, 255);
}


void Helper::renderBall() {
    SDL_Rect ballsrc = { HELPER_ANCHO, HELPER_ALTO, HELPER_ANCHO, HELPER_ALTO};
    SDL_Rect balldst = {(int) posicion.getX() - HELPER_RADIO_BALL,
                        (int) posicion.getY() - HELPER_RADIO_BALL,
                        HELPER_ANCHO, HELPER_ALTO};

    SDL_RenderCopy(gRenderer, textura, &ballsrc, &balldst);
}


void Helper::calcularVelocidad(){
    recorrido.pop_back();
    velocidad = (jugador->getPosicion() + posRelativa - posicion) * aceleracion;
    posicion = posicion + velocidad;
    recorrido.push_front(posicion);
}


void Helper::calcularAngulo(){
    if (jugador->getVelocidad().esNulo()) return;

    int angulo_d = (int) (jugador->getVelocidad().arg() - angulo + 180 + 360) % 360 - 180;

    if (abs(angulo_d) < velAngular) {
        angulo += angulo_d;
    }
    else {
        angulo += velAngular * ((angulo_d > 0) - (angulo_d < 0));
    }
    angulo = ((int) angulo + 360) % 360;
}


void Helper::renderHelper() {


    int renderPosX = (int) posicion.getX() - HELPER_RADIO_BALL + (int) (cos_d(angulo) * HELPER_DISTANCIA);
    int renderPosY = (int) posicion.getY() - HELPER_RADIO_BALL - (int) (sin_d(angulo) * HELPER_DISTANCIA);

    int angulo_trunc = ((int) angulo % 90) - 11;

    SDL_Rect helpersrc = { HELPER_ANCHO * (angulo_trunc >= 11)
                           + HELPER_ANCHO * (angulo_trunc >= 33)
                           + HELPER_ANCHO * (angulo_trunc >= 56)
                           - HELPER_ANCHO * 3 * (angulo_trunc >= 78),
                           0, HELPER_ANCHO, HELPER_ALTO};
    SDL_Rect helperdst = { renderPosX,
                           renderPosY,
                           HELPER_ANCHO, HELPER_ALTO};

    SDL_RenderCopyEx(gRenderer, textura, &helpersrc, &helperdst, -(int) (angulo / 90) * 90, nullptr, SDL_FLIP_NONE);

}


void Helper::render() {
    calcularAngulo();
    calcularVelocidad();

    renderGlow();
    renderBall();
    renderHelper();
}
