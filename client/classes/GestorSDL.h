#ifndef CUCURUCHO_GESTORSDL_H
#define CUCURUCHO_GESTORSDL_H


#include "view/ToastVista.h"

class GestorSDL {
public:
	bool init(int anchoPantallas, int altoPantalla);
	void close();
    bool event(std::string* inputText);

private:
	SDL_Window* gWindow = nullptr;
};


#endif //CUCURUCHO_GESTORSDL_H
