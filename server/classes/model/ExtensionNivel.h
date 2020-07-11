#ifndef CUCURUCHO_EXTENSIONNIVEL_H
#define CUCURUCHO_EXTENSIONNIVEL_H


#include "SemillaEntidad.h"
#include "EnemigoFinal1.h"
#include "CampoMovil.h"

class ExtensionNivel {
public:
	ExtensionNivel(CampoMovil* campoMovil, std::map<int, Jugador*>* jugadores);

	void iniciar();
	bool isIniciado();
	bool termino();

	void tick();

private:
	bool iniciado;
	CampoMovil* campo;
	EnemigoFinal1* enemigoFinal;
	int ticksPostMuerteEnemigoFinal;
	int maxTicksPostMuerteEnemigoFinal;
};


#endif //CUCURUCHO_EXTENSIONNIVEL_H
