//
// Created by camix on 9/7/20.
//

#include "Musica.h"
#include "../../commons/utils/Constantes.h"

Musica::Musica(Mix_Music* audio) {
    Musica::audio = audio;
    Musica::mute = false;
}

void Musica::play(int volumen) {

    Mix_PlayMusic(audio, -1);

    if (mute) Mix_VolumeMusic(0);
    else Mix_VolumeMusic(volumen);

}

void Musica::mutear() {

    mute = true;
    Mix_VolumeMusic(0);

}


void Musica::desmutear(){
    Musica::mute =false;
    Mix_VolumeMusic(90);

}