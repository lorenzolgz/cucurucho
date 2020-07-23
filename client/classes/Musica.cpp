//
// Created by camix on 9/7/20.
//

#include "Musica.h"

Musica::Musica(Mix_Music* audio) {
    Musica::audio = audio;
    Musica::currentKeyStates = SDL_GetKeyboardState(NULL);
    Musica::mute = false;

}

void Musica::play(int volumen) {

    Mix_PlayMusic(audio, -1);
    Mix_VolumeMusic(volumen);

}

void Musica::mutear() {

    if (currentKeyStates[SDL_SCANCODE_LCTRL] && currentKeyStates[SDL_SCANCODE_M] && !mute) {
        Mix_VolumeMusic(0);
        Musica::mute = true;
    }

}


void Musica::desmutear(){

    if (currentKeyStates[SDL_SCANCODE_LCTRL] && currentKeyStates[SDL_SCANCODE_M] && mute) {
        Mix_VolumeMusic(90);
        Musica::mute = false;
    }

}