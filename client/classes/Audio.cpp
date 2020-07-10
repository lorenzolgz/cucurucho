//
// Created by camix on 8/7/20.
//

#include <SDL_mixer.h>
#include "Audio.h"


Audio* Audio::instance=NULL;

Audio *Audio::getInstante() {

    if (instance==NULL) {
        instance = new Audio();
        l->error("Creando Audio");
    }
    return instance;

}

void Audio::generarAudio(std::string stringAudio) {

    const std::string& MUSIC_LOCATION = "../client/assets/music/";
    Audio::mixAudio = Mix_LoadMUS((MUSIC_LOCATION + stringAudio).c_str());

    if (mixAudio == nullptr) {
        l->error(std::string("Error al cargar el audio: ") + stringAudio + std::string(" ! Mix_Music Error:") + Mix_GetError());
    }

}

void Audio::generarSoundEffect(std::string stringSoundEffect){

    const std::string& SFX_LOCATION = "../client/assets/sfx/";
    mixSoundEffect = Mix_LoadWAV((SFX_LOCATION + stringSoundEffect).c_str());

    if (mixSoundEffect == nullptr) {
        l->error(std::string("Error al cargar el audio: ") + stringSoundEffect + std::string(" ! Mix_Music Error:") + Mix_GetError());
    }

}

void Audio::playMusic(int volumen) {

    if (mute) return;
    Mix_PlayMusic(mixAudio, -1);
    Mix_VolumeMusic(volumen);

}


void Audio::playSoundEffect(int volumen) {

    Mix_PlayChannel(-1, mixSoundEffect, 0);
    Mix_Volume(-1,volumen);

}

void Audio::mutear() {

    if (!mute) {
        Mix_HaltMusic();
        mute = true;
    }else {
        mute = false;
        playMusic(90);
    }

}


