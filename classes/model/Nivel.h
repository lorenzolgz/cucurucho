#ifndef CUCURUCHO_NIVEL_H
#define CUCURUCHO_NIVEL_H


#include "CampoMovil.h"
#include "Ticker.h"
#include "SemillaEntidad.h"

class Nivel : public Ticker {
public:
	Nivel(Configuracion* config, Jugador* jugador, int ancho, int alto);

    void crearEnemigos(Configuracion* config);
    //int crearEnemigos(int cantClase1, int cantClase2);
	void tick() override;
    void crearEnemigosDelTipo(int tipoDeEnemigo, int cantDeEnemigos);

private:
	int ancho;
	int alto;
	Hud* hud;
	CampoMovil* campo;
	list<SemillaEntidad*> semillasEntidades;
	int cantidadDeEnemigosACrear[2];
    int numeroDeNivel;
	CampoMovil *crearCampo(Configuracion *config, Jugador* jugador);
	void plantarSemillasEnCampo();
};


#endif //CUCURUCHO_NIVEL_H