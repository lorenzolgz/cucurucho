#ifndef CPP_SANDBOX_JUGADOR_H
#define CPP_SANDBOX_JUGADOR_H


#include <SDL_render.h>
#include <string>
#include "../../commons/utils/Vector.h"
#include "../../commons/protocols/protocolo.h"
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

class Jugador {
public:
    Jugador(ColoresJugador colores);
	void tick();
    int getContador() const;
    void setEstado(struct EstadoJugador estado);

private:
	struct EstadoJugador estado;
	Helper* helperAbove;
	Helper* helperBelow;
	JugadorVista *vista;
};


#endif //CPP_SANDBOX_JUGADOR_H
