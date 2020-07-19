//
// Created by camix on 9/7/20.
//

#include "EfectoSonido.h"
#include "../../commons/utils/Constantes.h"

EfectoSonido::EfectoSonido(Mix_Chunk *audio) {
	EfectoSonido::audio = audio;
	EfectoSonido::mute = !SONIDO_ACTIVADO;
}

void EfectoSonido::play(int volumen) {

	if (!mute) {
		Mix_PlayChannel(-1, audio, 0);
		Mix_Volume(-1, volumen);
	}
}


void EfectoSonido::mutear() {

    EfectoSonido::mute = true;
    Mix_Volume(-1, 0);

}


void EfectoSonido::desmutear(){

    EfectoSonido::mute =false;
    Mix_Volume(-1, 100);

}