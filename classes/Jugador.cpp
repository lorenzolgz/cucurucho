//
// Created by javier on 10/4/20.
//

#include "Jugador.h"
#include "Utils.h"
#include "Log.h"


Jugador::Jugador(SDL_Renderer* gRenderer, int x, int y) {
    velocidadEscalar = JUGADOR_VELOCIDAD_ESCALAR;
    posicion = Vector(x, y);
    velocidad = Vector(0, 0);
    contador = 0;
    contadorVelocidadY = 0;
    textura = cargarTextura(gRenderer, "player.png");
    texturaGlow = cargarTextura(gRenderer, "player.png");
    Jugador::gRenderer = gRenderer;
    l.info("Player created");
}

void Jugador::calcularVectorVelocidad(bool arriba, bool abajo, bool izquierda, bool derecha) {
    double vParcial = 0;

    if ((arriba || abajo) && (izquierda || derecha)) {
        vParcial = velocidadEscalar / sqrt(2);
    }
    else if (arriba || abajo || izquierda || derecha) {
        vParcial = velocidadEscalar;
    }

    double vx = 0, vy = 0;
    if (arriba) {
        vy = -vParcial;
        contadorVelocidadY += contadorVelocidadY < 14;
    }
    else if (abajo) {
        vy = vParcial;
        contadorVelocidadY -= contadorVelocidadY > -14;
    }
    else {
        contadorVelocidadY += (contadorVelocidadY < 0) - (contadorVelocidadY > 0);
    }

    if (izquierda) {
        vx = -vParcial;
    }
    else if (derecha) {
        vx = vParcial;
    }

    velocidad = Vector(vx, vy);
    posicion = posicion + velocidad;
}


void Jugador::colorGlow() {
    contador++;

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

    SDL_SetTextureColorMod(texturaGlow, COLORES[contador % 16][0], COLORES[contador % 16][1], COLORES[contador % 16][2]);
}


void Jugador::render() {
    SDL_Rect srcrect = {JUGADOR_ANCHO + JUGADOR_ANCHO * 2 * (contadorVelocidadY < -10) + JUGADOR_ANCHO * 4 * (contadorVelocidadY > 10),
                        0, JUGADOR_ANCHO, JUGADOR_ALTO};
    SDL_Rect dstrect = {(int) posicion.getX(),
                        (int) posicion.getY(),
                        JUGADOR_ANCHO,
                        JUGADOR_ALTO};

    SDL_RenderCopy(gRenderer, textura, &srcrect, &dstrect);

    colorGlow();
    srcrect = {JUGADOR_ANCHO * 2 * (contadorVelocidadY < -10) + JUGADOR_ANCHO * 4 * (contadorVelocidadY > 10),
               0, JUGADOR_ANCHO, JUGADOR_ALTO};
    SDL_RenderCopy(gRenderer, texturaGlow, &srcrect, &dstrect);

    l.info(("Position PLAYER:("+ std::to_string(posicion.getX())+","+ std::to_string(posicion.getY())+ ")"));
}

const Vector &Jugador::getPosicion() const {
    return posicion;
}

const Vector Jugador::getVelocidad() const {
    return velocidad;
}

int Jugador::getContador() const {
    return contador;
}
