#ifndef CUCURUCHO_NIVEL_H
#define CUCURUCHO_NIVEL_H


#include "algorithm"
#include <list>
#include <iostream>
#include "CampoMovil.h"
#include "Ticker.h"
#include "SemillaEntidad.h"
#include "../config/NivelConfiguracion.h"
#include "../states/EstadoInternoNivel.h"

#define PANTALLA_ANCHO 960
#define PANTALLA_ALTO 672

class Nivel : public Ticker {
public:
	Nivel(NivelConfiguracion* nivelConfig, Jugador* jugador);

	void crearEnemigos(int cantClase1, int cantClase2);
	void tick() override;
    void crearEnemigosDeClase(int tipoDeEnemigo, int cantDeEnemigos);
	bool termino();
	EstadoInternoCampoMovil state();

private:
	float ancho;
	int alto;
	Hud* hud;
	CampoMovil* campo;
	std::list<SemillaEntidad*> semillasEntidades;
    int numeroDeNivel;
    float velocidad;

	CampoMovil *crearCampo(NivelConfiguracion *nivelConfig, Jugador* jugador);
	void plantarSemillasEnCampo();
};


#endif //CUCURUCHO_NIVEL_H