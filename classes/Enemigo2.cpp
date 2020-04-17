//
// Created by camix on 15/4/20.
//

#include "Enemigo2.h"
#include <SDL_image.h>
#include "Utils.h"
#include "Log.h"

const int OFFSET_A = 200;
const int OFFSET_B = 500;

Enemigo2::Enemigo2(SDL_Renderer* gRenderer,float x,float y) {
    velocidadEscalar = 0.01;
    posicionx = x;
    posiciony = y;
    VelocidadX = true;
    textura = cargarTextura(gRenderer, "enemy02.png");
    texturaGlow = cargarTextura(gRenderer, "enemy02.png");
    Enemigo2::gRenderer = gRenderer;
    l.info("Enemy 02 created");
};

SDL_Rect Enemigo2::calcularMovimiento(float *x, float y, int width, int height) {

// Por si queremos mostrar como entra y sale en loop, moficando el sprite dependiendo
// si avanza o retrocede
//
//    if (posicionx > OFFSET and VelocidadX) {
//        *x -= velocidadEscalar;
//        if (posicionx == OFFSET_A) VelocidadX = false;
//    }
//    else{
//        *x += velocidadEscalar;
//        if (posicionx == OFFSET_B) VelocidadX = true;
//    }

    SDL_Rect dstrect;
    dstrect.x = *x;
    dstrect.y = y;
    dstrect.w = width;
    dstrect.h = height;

    return dstrect;


}

void Enemigo2::render() {
    SDL_Rect srcrect = {0, 0 + 49 * (VelocidadX), 95, 49};
    SDL_Rect dstrect = calcularMovimiento( &posicionx, posiciony, 95, 49);

    SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
    l.info(("Position ENEMY 02:("+ std::to_string(posicionx)+","+ std::to_string(posiciony)+ ")"));
}
