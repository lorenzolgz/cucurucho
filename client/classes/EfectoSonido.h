//
// Created by camix on 9/7/20.
//

#ifndef CUCURUCHO_EFECTOSONIDO_H
#define CUCURUCHO_EFECTOSONIDO_H


#include <SDL_mixer.h>

class EfectoSonido {
private:
    Mix_Chunk *audio;

public:

    EfectoSonido(Mix_Chunk* audio);

    void play(int volumen);

private:
	bool mute;
};


#endif //CUCURUCHO_EFECTOSONIDO_H
