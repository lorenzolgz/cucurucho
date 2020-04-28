#ifndef CUCURUCHO_NIVEL_H
#define CUCURUCHO_NIVEL_H


#include "CampoMovil.h"
#include "Ticker.h"
#include "SemillaEntidad.h"

class Nivel : public Ticker {
public:
	Nivel(Configuracion* config, Jugador* jugador, int ancho, int alto);

	void crearEnemigos(int cantClase1, int cantClase2);
	void tick() override;

private:
	int ancho;
	int alto;
	Hud* hud;
	CampoMovil* campo;
	list<SemillaEntidad*> semillasEntidades;

	void crearNEnemigo1(int n);
	void crearNEnemigo2(int n);
	CampoMovil *crearCampo(Configuracion *config, Jugador* jugador);
	void plantarSemillasEnCampo();
};


#endif //CUCURUCHO_NIVEL_H