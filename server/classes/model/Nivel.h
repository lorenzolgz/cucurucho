#ifndef CUCURUCHO_NIVEL_H
#define CUCURUCHO_NIVEL_H


#include "algorithm"
#include <list>
#include <iostream>
#include <map>
#include "CampoMovil.h"
#include "Ticker.h"
#include "SemillaEntidad.h"
#include "../config/NivelConfiguracion.h"
#include "../states/EstadoInternoNivel.h"
#include "entities/projectiles/Disparo.h"

class Nivel : public Ticker {
public:
	Nivel(NivelConfiguracion* nivelConfig, std::map<int, Jugador*>* jugador);

	void crearEnemigos(int cantClase1, int cantClase2);
	void tick() override;
    void crearEnemigosDeClase(int tipoDeEnemigo, int cantDeEnemigos);
	bool termino();
	EstadoInternoCampoMovil state();

    void nuevoDisparo(Disparo *pDisparo);

private:
	float largo;
	int alto;
	CampoMovil* campo;
	std::list<SemillaEntidad*> semillasEntidades;
	std::map<int, Jugador*>* jugadores;
    float velocidad;

	CampoMovil *crearCampo(std::map<int, Jugador*>* jugador);
	void plantarSemillasEnCampo();
};


#endif //CUCURUCHO_NIVEL_H