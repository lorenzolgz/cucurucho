//
// Created by camix on 9/7/20.
//

#include "Musica.h"

Musica::Musica(Mix_Music* audio) {
    Musica::audio = audio;

}

void Musica::play(int volumen) {

    Mix_PlayMusic(audio, -1);

}

void Musica::mutear() {

    Mix_VolumeMusic(0);

}


void Musica::desmutear(){

    Mix_VolumeMusic(90);

}