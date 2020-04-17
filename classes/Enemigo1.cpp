//
// Created by camix on 16/4/20.
//

#include "Enemigo1.h"
#include <SDL_image.h>
#include "Utils.h"
#include "Log.h"

const int OFFSET_A = 200;
const int OFFSET_B = 500;

Enemigo1::Enemigo1(SDL_Renderer* gRenderer, float x, float y) {
    velocidadEscalar = 0.01;
    posicionx = x;
    posiciony = y;
    VelocidadX = 7; // Posición 2 de sprite
    textura = cargarTextura(gRenderer, "enemy01.png");
    texturaGlow = cargarTextura(gRenderer, "enemy01.png");
    Enemigo1::gRenderer = gRenderer;
    l.info("Enemy 01 created");
};

SDL_Rect Enemigo1::calcularMovimiento(float *x, float y, int width, int height) {

    // Estapa 3 del TP: Movimientos del enemigo
    // Para determinar su posición y el sector del sprite

    SDL_Rect dstrect;
    dstrect.x = *x;
    dstrect.y = y;
    dstrect.w = width;
    dstrect.h = height;

    return dstrect;


}

void Enemigo1::render() {
    SDL_Rect srcrect = {0 + 22 * (VelocidadX < 10) * (VelocidadX > 5) + 44 * (VelocidadX > 10) * (VelocidadX < 15) + 66 * (VelocidadX > 15), 0 , 22, 22};
    SDL_Rect dstrect = calcularMovimiento( &posicionx, posiciony, 22, 22);

    SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
    l.info(("Position ENEMY 01:("+ std::to_string(posicionx)+","+ std::to_string(posiciony)+ ")"));
}
