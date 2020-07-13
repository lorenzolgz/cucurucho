#ifndef CUCURUCHO_CAMPOMOVIL_H
#define CUCURUCHO_CAMPOMOVIL_H


#include <list>
#include <map>
#include "Jugador.h"
#include "Ticker.h"
#include "EntidadEnemigo.h"
#include "../states/EstadoInternoCampoMovil.h"
#include "entities/projectiles/Disparo.h"

const int CAMPO_OFFSET = 300;

class Entidad;
class Ticker;
class Jugador;

class CampoMovil : public Ticker {
public:
	CampoMovil(std::map<int, Jugador*>* jugador, int ancho, int alto, float velocidadNivel, float largoNivel);

	int getAncho();
	int getAlto();
	Vector getPosicion();
	float getVelocidadX();
	void agregarEntidadEnemigo(EntidadEnemigo* entidad);
	bool entidadEstaDentroDelCampo(Entidad* entidad);
	void tick() override;

	bool verificarPosicionNivel();
	EstadoInternoCampoMovil state();
    void nuevoDisparo(EntidadDisparo *entidadDisparo);

    void nuevoDisparoEnemigo(EntidadDisparo *disparo);

private:
	int ancho;
	int alto;
	Vector posicion;
    float velocidadX;
    float largoNivel;
    std::map<int, Jugador*>* jugadores;
	std::list<EntidadEnemigo*> entidadesEnemigos;
    std::list<EntidadDisparo*> disparosJugador;
    std::list<EntidadDisparo*> disparosEnemigos;


    bool verificarEntidadEstaDentroDelCampo(Entidad* entidad);
	void procesarTodasLasColisiones();
	void procesarColisionEntreDosEntidades(Entidad* e1, Entidad* e2);
	void removerEntidadesEnemigosMuertas();
	void removerDisparosMuertos();
	void removerDisparosFueraDePantalla();
};


#endif //CUCURUCHO_CAMPOMOVIL_H
