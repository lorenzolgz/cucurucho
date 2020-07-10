//
// Created by camix on 8/7/20.
//

#ifndef CUCURUCHO_AUDIO_H
#define CUCURUCHO_AUDIO_H

#include <string>
#include <iostream>
#include "../../commons/utils/Log.h"
#include "Musica.h"
#include "EfectoSonido.h"
#include <SDL_mixer.h>

class Audio {
public:

    static Audio *getInstante();

    Musica *generarAudio(std::string audio);

    EfectoSonido *generarSoundEffect(std::string stringSoundEffect);


private:
    static Audio *instance;
    Mix_Music *mixAudio;
    Mix_Chunk *mixSoundEffect;

};


#endif //CUCURUCHO_AUDIO_H
