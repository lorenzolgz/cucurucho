//
// Created by camix on 9/7/20.
//

#ifndef CUCURUCHO_MUSICA_H
#define CUCURUCHO_MUSICA_H


#include <SDL_mixer.h>

class Musica {
private:
    Mix_Music *audio;
    bool mute;

public:

    Musica(Mix_Music* audio);

    void play(int volumen);

    void mutear();

    void desmutear();
};


#endif //CUCURUCHO_MUSICA_H
