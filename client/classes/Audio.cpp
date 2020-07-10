//
// Created by camix on 8/7/20.
//

#include <SDL_mixer.h>
#include "Audio.h"
#include "EfectoSonido.h"


Audio* Audio::instance=NULL;

Audio *Audio::getInstante() {

    if (instance==NULL) {
        instance = new Audio();
        l->error("Creando Audio");
    }
    return instance;

}

Musica *Audio::generarAudio(std::string stringAudio) {

    const std::string& MUSIC_LOCATION = "../client/assets/music/";
    Audio::mixAudio = Mix_LoadMUS((MUSIC_LOCATION + stringAudio).c_str());

    if (mixAudio == nullptr) {
        l->error(std::string("Error al cargar el audio: ") + stringAudio + std::string(" ! Mix_Music Error:") + Mix_GetError());
    }

    Musica *audio = new Musica(mixAudio);
    return audio;

}

EfectoSonido *Audio::generarSoundEffect(std::string stringSoundEffect){

    const std::string& SFX_LOCATION = "../client/assets/sfx/";
    mixSoundEffect = Mix_LoadWAV((SFX_LOCATION + stringSoundEffect).c_str());

    if (mixSoundEffect == nullptr) {
        l->error(std::string("Error al cargar el audio: ") + stringSoundEffect + std::string(" ! Mix_Music Error:") + Mix_GetError());
    }
    EfectoSonido *efecto = new EfectoSonido(mixSoundEffect);
    return efecto;

}

