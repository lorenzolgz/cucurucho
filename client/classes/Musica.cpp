//
// Created by camix on 9/7/20.
//

#include "Musica.h"
#include "../../commons/utils/Constantes.h"

Musica::Musica(Mix_Music* audio) {
    Musica::audio = audio;
    Musica::mute = !SONIDO_ACTIVADO;
}

void Musica::play(int volumen) {

    if (mute) return;
    Mix_PlayMusic(audio, -1);
    Mix_VolumeMusic(volumen);
}

void Musica::mutear() {

    if (!mute) {
        Mix_HaltMusic();
        mute = true;
    }else {
        mute = false;
        play(90);
    }

}


