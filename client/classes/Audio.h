//
// Created by camix on 8/7/20.
//

#ifndef CUCURUCHO_AUDIO_H
#define CUCURUCHO_AUDIO_H

#include <string>
#include <iostream>
#include "../../commons/utils/Log.h"
#include <SDL_mixer.h>

class Audio {
public:

    static Audio *getInstante();

    void generarAudio(std::string audio);

    void generarSoundEffect(std::string stringSoundEffect);

    void playMusic(int volumen);

    void playSoundEffect(int volumen);

    void mutear();

private:
    static Audio *instance;
    Mix_Music *mixAudio;
    Mix_Chunk *mixSoundEffect;
    bool mute = false;

};


#endif //CUCURUCHO_AUDIO_H
