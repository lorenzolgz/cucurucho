//
// Created by camix on 9/7/20.
//

#ifndef CUCURUCHO_MUSICA_H
#define CUCURUCHO_MUSICA_H


#include <SDL_mixer.h>
#include <SDL_system.h>

#define VOLUMEN_MUSICA 60
#define VOLUMEN_MUTE 0


class Musica {
private:
    Mix_Music *audio;

public:

    Musica(Mix_Music* audio);

    ~Musica();

    void play(int volumen);

    void mutear();

    void desmutear();

};


#endif //CUCURUCHO_MUSICA_H
