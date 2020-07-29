//
// Created by camix on 9/7/20.
//

#include "Musica.h"

Musica::Musica(Mix_Music* audio) {
    Musica::audio = audio;

}

void Musica::play(int volumen) {

    Mix_PlayMusic(audio, -1);
    Mix_VolumeMusic(volumen);

}

void Musica::mutear() {

    Mix_VolumeMusic(VOLUMEN_MUTE);

}


void Musica::desmutear(){

    Mix_VolumeMusic(VOLUMEN_MUSICA);

}