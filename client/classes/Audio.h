//
// Created by camix on 8/7/20.
//

#ifndef CUCURUCHO_AUDIO_H
#define CUCURUCHO_AUDIO_H

#include <string>
#include <iostream>
#include "../../commons/utils/Log.h"
#include "Musica.h"
#include "EfectoSonido.h"
#include <SDL_mixer.h>
#include <string.h>
#include <map>
#include <iostream>
#include "../../commons/utils/Constantes.h"

class Audio {
public:

    Audio();

    static Audio *getInstance();

    Musica *generarMusica(std::string audio);

    EfectoSonido *cargarEfectosSonido(std::string stringSoundEffect);

    EfectoSonido* generarEfecto(std::string soundEffect);

    Musica *cargarMusica(std::string stringAudio);


    void mutear();

    void playMusic(std::string cancion);

    void playEffect(std::string efecto);

private:
    static Audio *instance;
    bool mute;
    Mix_Music *mixAudio;
    Mix_Chunk *mixSoundEffect;
    std::map<std::string, EfectoSonido *> efectos;
    std::map<std::string, Musica *> canciones;
    EfectoSonido * efecto_defecto;
    Musica * musica_defecto;

};


#endif //CUCURUCHO_AUDIO_H
