#ifndef CPP_SANDBOX_JUGADOR_H
#define CPP_SANDBOX_JUGADOR_H


#include <string>
#include "../../../commons/utils/Vector.h"
#include "../../../commons/protocols/protocolo.h"
#include "Helper.h"
#include "entities/Entidad.h"
#include "life/VidaJugadorMortal.h"

class CampoMovil;
class Helper;
class Entidad;

const int JUGADOR_ANCHO = 96;
const int JUGADOR_ALTO = 48;
const int TICKS_COOLDOWN_DISPARO = 100;
const double JUGADOR_VELOCIDAD_ESCALAR = 4.5;

class Jugador : public Entidad {
public:
    Jugador(int x, int y);
	void calcularVectorVelocidad(bool arriba, bool abajo, bool izquierda, bool derecha);
	void tick();
	struct EstadoJugador state();

	Vector getPosicion() override;
	int getAncho() override;
	int getAlto() override;
	int getTipoEntidad() override;
	std::list<Forma> getFormas() override;

	const Vector &getPosicion() const;
    const Vector getVelocidad() const;
    void setPosicion(int x, int y);
    void setCampo(CampoMovil* campo);
    bool puedeDisparar();
    bool disparar();
    void resetState();
	VidaEntidad* getVidaEntidad();

private:
    Vector posicion;
    Vector velocidad;
    double velocidadEscalar;
    int ticksHastaDisparo;

	CampoMovil* campo;
	Helper* helperAbove;
	Helper* helperBelow;
	VidaEntidad* vida;

	Vector actualizarPosicion(Vector posicionNueva);
};


#endif //CPP_SANDBOX_JUGADOR_H
