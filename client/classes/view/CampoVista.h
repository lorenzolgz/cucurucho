#ifndef CUCURUCHO_CAMPOVISTA_H
#define CUCURUCHO_CAMPOVISTA_H


#include <list>
#include <vector>
#include "elements/FondoVista.h"
#include "../../../commons/protocols/protocolo.h"

class CampoVista {
public:
	CampoVista(float velocidadMovilX, int numeroNivel);
	FondoVista * nuevoFondo(const std::string &fileName, float xOffset, int yFondo, float modVelocidad);
	void render(EstadoTick tick);

	int getNumeroNivel() const;

private:
	SDL_Renderer* gRenderer;
	float velocidadNivel;
	float posX;
	int ultimoTick;
	int numeroNivel;
	std::list<FondoVista*> fondos;

};


#endif //CUCURUCHO_CAMPOVISTA_H
