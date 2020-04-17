//
// Created by camix on 16/4/20.
//

#include "Enemigo1.h"
#include <SDL_image.h>
#include "Utils.h"
#include "Log.h"


Enemigo1::Enemigo1(SDL_Renderer* gRenderer, float x, float y) {
    velocidadEscalar = 0.01;
    posicion = Vector(x, y);
    VelocidadX = 7; // Posición 2 de sprite
    textura = cargarTextura(gRenderer, "enemy01.png");
    texturaGlow = cargarTextura(gRenderer, "enemy01.png");
    Enemigo1::gRenderer = gRenderer;
    l.info("Enemy 01 created");
};

SDL_Rect Enemigo1::calcularMovimiento(int width, int height) {

    // Etapa 3 del TP: Movimientos del enemigo
    // Para determinar su posición y el sector del sprite

    SDL_Rect dstrect;
    dstrect.x = (int) posicion.getX();
    dstrect.y = (int) posicion.getY();
    dstrect.w = width;
    dstrect.h = height;

    return dstrect;


}

void Enemigo1::render() {
    SDL_Rect srcrect = {0 + ENEMIGO1_ANCHO * (VelocidadX < 10) * (VelocidadX > 5)
                        + ENEMIGO1_ANCHO * 2 * (VelocidadX > 10) * (VelocidadX < 15)
                        + ENEMIGO1_ANCHO * 3 * (VelocidadX > 15),
                        0 , ENEMIGO1_ANCHO, ENEMIGO1_ALTO};
    SDL_Rect dstrect = calcularMovimiento(ENEMIGO1_ANCHO, ENEMIGO1_ALTO);

    SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
    l.info(("Position ENEMY 01:("+ std::to_string(posicion.getX())+","+ std::to_string(posicion.getX())+ ")"));
}
