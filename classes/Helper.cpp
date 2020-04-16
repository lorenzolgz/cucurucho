//
// Created by javier on 12/4/20.
//

#include <iostream>
#include "Helper.h"
#include "Utils.h"

const int RADIO_BALL = 8;
const int DISTANCE_HELPER = 9;

const double VEL_ANGULAR = 15;
const double ACELERACION = 0.2;

Helper::Helper(SDL_Renderer *gRenderer, Jugador* jugador, Vector posRelativa) {
    Helper::gRenderer = gRenderer;
    Helper::jugador = jugador;
    Helper::posRelativa = posRelativa;
    Helper::posicion = posRelativa + jugador->getPosicion();
    Helper::velocidad = Vector(0, 0);
    Helper::velAngular = VEL_ANGULAR;
    Helper::aceleracion = ACELERACION;
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

    SDL_Rect glowsrc = { 0, 16, 16, 16};
    SDL_Rect glowdst = {(int) posicion.getX() - RADIO_BALL,
                        (int) posicion.getY() - RADIO_BALL,
                        16, 16};

    SDL_RenderCopy(gRenderer, textura, &glowsrc, &glowdst);


    if (contador % 6 < 3) {
        // Una de las tres posibles particulas [0, 1, 2]
        int glow = contador % 6;
        glowsrc = {16 * glow, 32, 16, 16};
        glowdst = { (int) recorrido[6 * (glow + 1)].getX() - RADIO_BALL,
                    (int) recorrido[6 * (glow + 1)].getY() - RADIO_BALL,
                    16, 16};
        SDL_RenderCopy(gRenderer, textura, &glowsrc, &glowdst);
    }

    SDL_SetTextureColorMod(textura, 255, 255, 255);
}


void Helper::renderBall() {
    SDL_Rect ballsrc = { 16, 16, 16, 16};
    SDL_Rect balldst = {(int) posicion.getX() - RADIO_BALL,
                        (int) posicion.getY() - RADIO_BALL,
                        16, 16};

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


    int renderPosX = (int) posicion.getX() - RADIO_BALL + (int) (cos_d(angulo) * DISTANCE_HELPER);
    int renderPosY = (int) posicion.getY() - RADIO_BALL - (int) (sin_d(angulo) * DISTANCE_HELPER);

    int angulo_trunc = ((int) angulo % 90) - 11;

    SDL_Rect helpersrc = { 16 * (angulo_trunc >= 11) + 16 * (angulo_trunc >= 33) + 16 * (angulo_trunc >= 56) - 48 * (angulo_trunc >= 78),
                           0, 16, 16};
    SDL_Rect helperdst = { renderPosX,
                           renderPosY,
                           16, 16};

    SDL_RenderCopyEx(gRenderer, textura, &helpersrc, &helperdst, -(int) (angulo / 90) * 90, nullptr, SDL_FLIP_NONE);

}


void Helper::render() {
    calcularAngulo();
    calcularVelocidad();

    renderGlow();
    renderBall();
    renderHelper();
}
