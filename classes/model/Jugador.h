#ifndef CPP_SANDBOX_JUGADOR_H
#define CPP_SANDBOX_JUGADOR_H


#include <SDL_render.h>
#include <string>
#include "../Vector.h"
#include "../view/JugadorVista.h"
#include "../GeneradorDeTexturas.h"
#include "Helper.h"
#include "Entidad.h"

class CampoMovil;
class Helper;
class HelperVista;
class Entidad;

const int JUGADOR_ANCHO = 96;
const int JUGADOR_ALTO = 48;

const double JUGADOR_VELOCIDAD_ESCALAR = 4.5;

class Jugador : public Entidad {
public:
	Jugador(int x, int y);
	void calcularVectorVelocidad(bool arriba, bool abajo, bool izquierda, bool derecha);
	void tick();

	int getAncho() override;

	int getAlto() override;

	Vector getPosicion() override;

	const Vector &getPosicion() const;
    const Vector getVelocidad() const;
    int getContador() const;
    void setPosicion(int x, int y);
    void setCampo(CampoMovil* campo);

private:
    Vector posicion;
    Vector velocidad;
    double velocidadEscalar;
    int contadorVelocidadY;

	CampoMovil* campo;
	Helper* helperAbove;
	Helper* helperBelow;

	JugadorVista *vista;

	Vector actualizarPosicion(Vector posicionNueva);
};


#endif //CPP_SANDBOX_JUGADOR_H
