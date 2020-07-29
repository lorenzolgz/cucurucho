//
// Created by camix on 9/7/20.
//

#ifndef CUCURUCHO_EFECTOSONIDO_H
#define CUCURUCHO_EFECTOSONIDO_H

#include <SDL_mixer.h>

#define VOLUMEN_EFECTO 100
#define VOLUMEN_MUTE 0

class EfectoSonido {
private:
    Mix_Chunk *audio;

public:

    EfectoSonido(Mix_Chunk* audio);

    void play(int volumen);

    void desmutear();

    void mutear();
};


#endif //CUCURUCHO_EFECTOSONIDO_H
