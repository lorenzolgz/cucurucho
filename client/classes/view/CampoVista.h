#ifndef CUCURUCHO_CAMPOVISTA_H
#define CUCURUCHO_CAMPOVISTA_H


#include <list>
#include <vector>
#include "../view/FondoVista.h"
#include "../../../commons/protocols/protocolo.h"

class CampoVista {
public:
	CampoVista(float velocidadMovilX);
	FondoVista * nuevoFondo(const std::string &fileName, float xOffset, int yFondo, float modVelocidad);
	void render(EstadoTick tick);

private:
	SDL_Renderer* gRenderer;
	float velocidadNivel;
	float posX;
	std::list<FondoVista*> fondos;

};


#endif //CUCURUCHO_CAMPOVISTA_H
