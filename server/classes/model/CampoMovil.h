#ifndef CUCURUCHO_CAMPOMOVIL_H
#define CUCURUCHO_CAMPOMOVIL_H


#include <list>
#include <map>
#include "Jugador.h"
#include "Ticker.h"
#include "EntidadEnemigo.h"
#include "../states/EstadoInternoCampoMovil.h"
#include "Disparo.h"

const int CAMPO_OFFSET = 300;

class Entidad;
class Ticker;
class Jugador;

class CampoMovil : public Ticker {
public:
	CampoMovil(std::map<int, Jugador *> jugador, int ancho, int alto, int inicioEnEjeY, float velocidadNivel, float largoNivel);

	int getAncho();
	int getAlto();
	Vector getPosicion();
	float getVelocidadX();
	void agregarEntidadEnemigo(EntidadEnemigo* entidad);
	bool entidadEstaDentroDelCampo(Entidad* entidad);
	void tick() override;

	bool verificarPosicionNivel();
	EstadoInternoCampoMovil state();


    bool nuevoDisparo(Disparo *pDisparo);

private:
	int ancho;
	int alto;
	Vector posicion;
    float velocidadX;
    float largoNivel;
    std::map<int, Jugador *> jugadores;
	std::list<EntidadEnemigo*> entidadesEnemigos;
	std::list<Disparo*> disparos;

    bool verificarPosicionEnemigo(EntidadEnemigo *pEnemigo);
	bool verificarPosicionDisparo(Disparo *pDisparo);
	void procesarColisiones();
	void removerEntidadesEnemigosMuertas();
};


#endif //CUCURUCHO_CAMPOMOVIL_H
