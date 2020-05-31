#ifndef CUCURUCHO_CAMPOMOVIL_H
#define CUCURUCHO_CAMPOMOVIL_H


#include <list>
#include "Hud.h"
#include "Jugador.h"
#include "Ticker.h"
#include "EntidadEnemigo.h"
#include "../states/EstadoInternoCampoMovil.h"

class Entidad;
class Ticker;
class Jugador;

class CampoMovil : public Ticker {
public:
	CampoMovil(Jugador* jugador, int ancho, int alto, int inicioEnEjeY, float velocidadNivel, float largoNivel);

	int getAncho();
	int getAlto();
	Vector getPosicion();
	float getVelocidadX();
	void agregarEntidadEnemigo(EntidadEnemigo* entidad);
	bool entidadEstaDentroDelCampo(Entidad* entidad);
	void tick() override;

	bool verificarPosicion();
	EstadoInternoCampoMovil state();


private:
	int ancho;
	int alto;
	Vector posicion;
    float velocidadX;
    float largoNivel;
    Jugador* jugador;
	std::list<EntidadEnemigo*> entidadesEnemigos;
};


#endif //CUCURUCHO_CAMPOMOVIL_H