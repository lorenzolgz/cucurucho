//
// Created by camix on 9/7/20.
//

#include "EfectoSonido.h"

EfectoSonido::EfectoSonido(Mix_Chunk *audio) {
	EfectoSonido::audio = audio;

}

void EfectoSonido::play(int volumen) {

    Mix_PlayChannel(-1, audio, 0);
	Mix_Volume(-1, volumen);

}


void EfectoSonido::mutear() {

    Mix_Volume(-1, VOLUMEN_MUTE);

}


void EfectoSonido::desmutear(){

    Mix_Volume(-1, VOLUMEN_EFECTO);

}