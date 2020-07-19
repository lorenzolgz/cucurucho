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
//    efecto_defecto = cargarEfectosSonido("sfx-01.wav");
//    musica_defecto = cargarMusica("rainonme.mpeg");
    Audio::mute = false;
    l->info("Creacion de instancia GeneradorDeTexturas");
}

EfectoSonido* Audio::generarEfecto(std::string soundEffect) {
    EfectoSonido* efecto = efectos[soundEffect];

    if (efecto == NULL){
        efectos[soundEffect] = cargarEfectosSonido(soundEffect);
        efecto = efectos[soundEffect];
    }

    if (efecto == NULL){
        return efecto_defecto;
    }
    return efecto;
}


Musica* Audio::generarMusica(std::string cancion) {
    Musica* musica = canciones[cancion];

    if (musica == NULL){
        canciones[cancion] = cargarMusica(cancion);
        musica = canciones[cancion];
    }

    if (musica == NULL){
        return musica_defecto;
    }
    return musica;
}

void Audio::mutear() {
    std::map<std::string, Musica *>::iterator it;
    if (!mute) {

        for (it = canciones.begin(); it != canciones.end(); it++) {

            it->second->mutear();
        }
        Audio::mute = true;
    }
    else{

        for (it = canciones.begin(); it != canciones.end(); it++) {
            it->second->desmutear();
        }
        Audio::mute = false;
    }
}
void Audio::playMusic(std::string cancion) {
    std::cout<<Audio::mute<<std::endl;

    int volumen;
    std::map<std::string, Musica*>::iterator it = canciones.find(cancion);
    if (mute) volumen = 0;
    else volumen = 100;

    if(it == canciones.end())
        musica_defecto->play(volumen);
    else
       it->second->play(volumen);
}
