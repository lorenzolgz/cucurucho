#ifndef CUCURUCHO_GESTORSDL_H
#define CUCURUCHO_GESTORSDL_H


#include "view/ToastVista.h"
#include "Audio.h"

class GestorSDL {
public:
	bool init(int anchoPantallas, int altoPantalla);

	void close();

    bool event(std::string* inputText);

    bool reproducirMusica(std::string stringAudio);

    void mutear();

private:
	SDL_Window* gWindow = nullptr;
//    Musica* musica;

};


#endif //CUCURUCHO_GESTORSDL_H
