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

class CampoMovil : public Ticker {
public:
	CampoMovil(Jugador* jugador, int ancho, int alto, int inicioEnEjeY, float velocidadNivel, float largoNivel);

	int getAncho();
	int getAlto();
	Vector getPosicion();
	float getVelocidadX();
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
    float largoNivel;
    Jugador* jugador;
    CampoVista* vista;
	std::list<Entidad*> entidades;
};


#endif //CUCURUCHO_CAMPOMOVIL_H