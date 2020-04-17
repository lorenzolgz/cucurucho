//
// Created by camix on 15/4/20.
//

#include "Enemigo2.h"
#include <SDL_image.h>
#include "Utils.h"
#include "Log.h"

const int OFFSET_A = 600;
const int OFFSET_B = 1500;

Enemigo2::Enemigo2(SDL_Renderer* gRenderer,float x,float y) {
    velocidadEscalar = 1;
    posicion = Vector(x, y);
    VelocidadX = true;
    textura = cargarTextura(gRenderer, "enemy02.png");
    Enemigo2::gRenderer = gRenderer;
    l.info("Enemy 02 created");
};

SDL_Rect Enemigo2::calcularMovimiento(int width, int height) {

// Por si queremos mostrar como entra y sale en loop, moficando el sprite dependiendo
// si avanza o retrocede
//
    if (posicion.getX() > OFFSET_A and VelocidadX) {
        posicion = posicion + Vector(-velocidadEscalar, 0);
        if (posicion.getX() <= OFFSET_A) VelocidadX = false;
    }
    else{
        posicion = posicion + Vector(velocidadEscalar, 0);
        if (posicion.getX() >= OFFSET_B) VelocidadX = true;
    }

    SDL_Rect dstrect;
    dstrect.x = (int) posicion.getX();
    dstrect.y = (int) posicion.getY();
    dstrect.w = width;
    dstrect.h = height;

    return dstrect;


}

void Enemigo2::render() {
    SDL_Rect srcrect = {0, 0 + ENEMIGO2_ALTO * (VelocidadX), ENEMIGO2_ANCHO, ENEMIGO2_ALTO};
    SDL_Rect dstrect = calcularMovimiento(ENEMIGO2_ANCHO, ENEMIGO2_ALTO);

    SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);
    l.info(("Position ENEMY 02:("+ std::to_string(posicion.getX())+","+ std::to_string(posicion.getY())+ ")"));
}
