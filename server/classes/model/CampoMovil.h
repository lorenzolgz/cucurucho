#ifndef CUCURUCHO_CAMPOMOVIL_H
#define CUCURUCHO_CAMPOMOVIL_H


#include <list>
#include <map>
#include "Hud.h"
#include "Jugador.h"
#include "Ticker.h"
#include "EntidadEnemigo.h"
#include "../states/EstadoInternoCampoMovil.h"

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


private:
	int ancho;
	int alto;
	Vector posicion;
    float velocidadX;
    float largoNivel;
    std::map<int, Jugador *> jugadores;
	std::list<EntidadEnemigo*> entidadesEnemigos;

    bool verificarPosicionEnemigo(EntidadEnemigo *pEnemigo);
    void procesarColisiones();
	void removerEntidadesEnemigosMuertas();
};


#endif //CUCURUCHO_CAMPOMOVIL_H