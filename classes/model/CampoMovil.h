#ifndef CUCURUCHO_CAMPOMOVIL_H
#define CUCURUCHO_CAMPOMOVIL_H


#include "Hud.h"
#include "../config/Configuracion.h"
#include "../view/CampoVista.h"
#include "Jugador.h"
#include "Ticker.h"
#include "Entidad.h"

class Entidad;
class Ticker;
#define TIEMPO_NIVEL 500

class CampoMovil : public Ticker {
public:
	CampoMovil(Jugador* jugador, int ancho, int alto, int inicioEnEjeY, int velocidadNivel);

	int getAncho();
	int getAlto();
	Vector getPosicion();
	int getVelocidadX();
	void agregarEntidad(Entidad* entidad);
	FondoVista *nuevoFondo(const std::string &fileName, float xOffset, int yFondo, float modVelocidad);
	bool entidadEstaDentroDelCampo(Entidad* entidad);
	void tick() override;

	bool verificarPosicion();


private:
	int ancho;
	int alto;
	Vector posicion;
	float velocidadX;
	Jugador* jugador;
	CampoVista* vista;
	std::list<Entidad*> entidades;

};


#endif //CUCURUCHO_CAMPOMOVIL_H