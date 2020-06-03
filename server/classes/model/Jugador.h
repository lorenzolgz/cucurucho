#ifndef CPP_SANDBOX_JUGADOR_H
#define CPP_SANDBOX_JUGADOR_H


#include <string>
#include "../../../commons/utils/Vector.h"
#include "../../../commons/protocols/protocolo.h"
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
	struct EstadoJugador state();

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

	CampoMovil* campo;
	Helper* helperAbove;
	Helper* helperBelow;

	Vector actualizarPosicion(Vector posicionNueva);
};


#endif //CPP_SANDBOX_JUGADOR_H
