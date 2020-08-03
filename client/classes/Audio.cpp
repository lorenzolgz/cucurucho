//
// Created by camix on 8/7/20.
//

#include <SDL_mixer.h>
#include "Audio.h"
#include "EfectoSonido.h"

Audio* Audio::instance=NULL;

Audio *Audio::getInstance() {

    if (instance==NULL) {
        instance = new Audio();
        l->info("Creando Audio");
    }
    return instance;

}


Musica *Audio::cargarMusica(std::string stringAudio) {

    const std::string& MUSIC_LOCATION = "../client/assets/music/";
    Audio::mixAudio = Mix_LoadMUS((MUSIC_LOCATION + stringAudio).c_str());

    if (mixAudio == nullptr) {
        l->error(std::string("Error al cargar el audio: ") + stringAudio + std::string(" ! Mix_Music Error:") + Mix_GetError());
    }

    Musica *audio = new Musica(mixAudio);
    return audio;

}

EfectoSonido *Audio::cargarEfectosSonido(std::string stringSoundEffect){

    const std::string& SFX_LOCATION = "../client/assets/sfx/";
    mixSoundEffect = Mix_LoadWAV((SFX_LOCATION + stringSoundEffect).c_str());

    if (mixSoundEffect == nullptr) {
        l->error(std::string("Error al cargar el audio: ") + stringSoundEffect + std::string(" ! Mix_Music Error:") + Mix_GetError());
    }
    EfectoSonido *efecto = new EfectoSonido(mixSoundEffect);
    return efecto;
}

Audio::Audio(){

    efecto_defecto = cargarEfectosSonido("sfx-01.wav");
    musica_defecto = cargarMusica("blank.mp3");
    Audio::mute = !SONIDO_ACTIVADO;

    l->info("Creacion de instancia GeneradorDeTexturas");
}

void Audio::generarEfecto(std::string soundEffect) {
    EfectoSonido* efecto = efectos[soundEffect];

    if (efecto == nullptr){
        efectos[soundEffect] = cargarEfectosSonido(soundEffect);
    }

}


void Audio::generarMusica(std::string cancion) {
    Musica* musica = canciones[cancion];

    if (musica == nullptr) {
		if (!canciones.empty()) {
			auto it = canciones.begin();
			delete it->second;
			canciones.erase(it);
		}
        canciones[cancion] = cargarMusica(cancion);
    }

}

void Audio::mutear() {
    if (mute) {
        std::map<std::string, Musica *>::iterator it1;
        std::map<std::string, EfectoSonido *>::iterator it2;

        for (it1 = canciones.begin(); it1 != canciones.end(); it1++) {
            it1->second->desmutear();
        }
        for (it2 = efectos.begin(); it2 != efectos.end(); it2++) {
            it2->second->desmutear();
        }

        Audio::mute = false;
    }
    else{
        std::map<std::string, Musica *>::iterator it1;
        std::map<std::string, EfectoSonido *>::iterator it2;

        for (it1 = canciones.begin(); it1 != canciones.end(); it1++) {
            it1->second->mutear();
        }
        for (it2 = efectos.begin(); it2 != efectos.end(); it2++) {
            it2->second->mutear();
        }

        Audio::mute = true;
    }
}


void Audio::playMusic(std::string cancion) {

	int volumen;
	auto it = canciones.find(cancion);

	if (!mute) volumen = VOLUMEN_MUSICA;
	else volumen = VOLUMEN_MUTE;

	if(it == canciones.end())
		musica_defecto->play(volumen);
	else
		it->second->play(volumen);
}

void Audio::stopMusic() {
	Mix_HaltMusic();
}

void Audio::playEffect(std::string efecto) {
	generarEfecto(efecto);
    int volumen;
    auto it = efectos.find(efecto);

    if (!mute) volumen = VOLUMEN_EFECTO;
    else volumen = VOLUMEN_MUTE;

    if(it == efectos.end())
        efecto_defecto->play(volumen);
    else
        it->second->play(volumen);
}

