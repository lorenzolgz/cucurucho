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
class Disparo;

const int JUGADOR_ANCHO = 96;
const int JUGADOR_ALTO = 48;
const int TICKS_COOLDOWN_DISPARO = 18;
const double JUGADOR_VELOCIDAD_ESCALAR = 5.75;

class Jugador : public Entidad {
public:
	Jugador(Configuracion* config, int nroJugador);
	~Jugador();
	void calcularVectorVelocidad(bool arriba, bool abajo, bool izquierda, bool derecha);
	void tick();
	struct EstadoJugador state();

	int getTipoEntidad() override;
	VidaEntidad* getVidaEntidad() override;

    const Vector getVelocidad() const;
    void setCampo(CampoMovil* campo);
	std::list<Disparo*> disparar();
    void reiniciarPosicion();
	void cambiarInvencible(bool invencible);
	bool estaMuerto();
	void setDesconectado(bool nuevoDesconectado);
	bool estaDesconectado();
    void sumarPuntosPorDestruirA(int entidadEnemigo);
    int getNroJugador();
    void finNivel();

private:
	Configuracion* config;
	int nroJugador;
	int puntos;
	std::list<int> puntosParcial;
    Vector velocidad;
    double velocidadEscalar;
    int ticksHastaDisparo;
	bool agregarPuntajeParcial;
	CampoMovil* campo;
	Helper* helperAbove;
	Helper* helperBelow;
	VidaJugador* vida;
    bool desconectado;

	Vector actualizarPosicion(Vector posicionNueva);
	bool puedeDisparar();
	Vector calcularPosicionInicial();


    int acumulado;
};


#endif //CPP_SANDBOX_JUGADOR_H
