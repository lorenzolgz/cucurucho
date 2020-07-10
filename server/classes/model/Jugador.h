#ifndef CPP_SANDBOX_JUGADOR_H
#define CPP_SANDBOX_JUGADOR_H


#include <string>
#include "../../../commons/utils/Vector.h"
#include "../../../commons/protocols/protocolo.h"
#include "Helper.h"
#include "entities/Entidad.h"
#include "life/VidaJugador.h"
#include "entities/projectiles/Disparo.h"
#include "../config/Configuracion.h"

class CampoMovil;
class Helper;
class Entidad;

const int JUGADOR_ANCHO = 96;
const int JUGADOR_ALTO = 48;
const int TICKS_COOLDOWN_DISPARO = 30;
const double JUGADOR_VELOCIDAD_ESCALAR = 4.5;

class Jugador : public Entidad {
public:
    Jugador(Configuracion* config, int nroJugador);
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
    void setCampo(CampoMovil* campo);
    // Todo: cada jugador tendria que saber su nroJugador de antemano!!!!
    Disparo* disparar();
    void reiniciarPosicion();
	VidaEntidad* getVidaEntidad();
	void cambiarInvencible(bool invencible);
	bool estaMuerto();

private:
	Configuracion* config;
	int nroJugador;
    Vector posicion;
    Vector velocidad;
    double velocidadEscalar;
    int ticksHastaDisparo;

	CampoMovil* campo;
	Helper* helperAbove;
	Helper* helperBelow;
	VidaJugador* vida;

	Vector actualizarPosicion(Vector posicionNueva);
	bool puedeDisparar();
	Vector calcularPosicionInicial();
};


#endif //CPP_SANDBOX_JUGADOR_H
