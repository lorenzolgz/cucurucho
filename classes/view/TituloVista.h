//
// Created by javier on 10/5/20.
//

#ifndef CUCURUCHO_TITULOVISTA_H
#define CUCURUCHO_TITULOVISTA_H

#include <SDL_render.h>
#include <SDL_rect.h>
#include <set>

class TituloParticula;

class TituloVista {
    SDL_Texture* texturaTitulo;
    SDL_Texture* texturaParticulas;
    int alto;
    int ancho;
    int contador;
    int contadorActivada;
    SDL_Renderer* gRenderer;
    std::set<TituloParticula*> particulas;
public:
    TituloVista(int ancho, int alto);
    void render(bool b);

    void nuevaParticula();

    void renderParticulas();

    void renderTitulo();

    void renderTextos(bool b);

    void renderFadeout(bool activada);
};


#endif //CUCURUCHO_TITULOVISTA_H
