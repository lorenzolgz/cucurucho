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

class Audio {
public:

    Audio();

    static Audio *getInstante();

    Musica *generarMusica(std::string audio);

    EfectoSonido *cargarEfectosSonido(std::string stringSoundEffect);

    EfectoSonido* generarEfecto(std::string soundEffect);

    Musica *cargarMusica(std::string stringAudio);


private:
    static Audio *instance;
    Mix_Music *mixAudio;
    Mix_Chunk *mixSoundEffect;
    std::map<std::string, EfectoSonido *> efectos;
    std::map<std::string, Musica *> canciones;
    EfectoSonido * efecto_defecto;
    Musica * musica_defecto;

};


#endif //CUCURUCHO_AUDIO_H
