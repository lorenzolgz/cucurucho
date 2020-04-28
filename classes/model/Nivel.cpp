#include <algorithm>
#include "Nivel.h"
#include "Enemigo2.h"
#include "Enemigo1.h"
#include "Jugador.h"

Nivel::Nivel(Configuracion* config, Jugador* jugador, int ancho, int alto) {
	Nivel::hud = new Hud();
	Nivel::campo = crearCampo(config, jugador);
	Nivel::ancho = ancho;
	Nivel::alto = campo->getAlto();
}

void Nivel::tick() {
	campo->tick();
	hud->tick();
	plantarSemillasEnCampo();
}

void Nivel::crearEnemigos(int cantClase1, int cantClase2) {
	crearNEnemigo2(cantClase2);
	crearNEnemigo1(cantClase1);
}

void Nivel::crearNEnemigo1(int n) {
	for (int i = 0; i < n; i++) {
		int posInicialX = campo->getAncho();
		int posY = std::rand() % alto;
		// !!!! acomodar esto:
		int posXEnNivel = std::rand() % 600 + campo->getAncho();
		int velocidadX = campo->getVelocidadX();

		Entidad* entidad = new Enemigo1(posInicialX, posY, velocidadX);
		SemillaEntidad* semillaEntidad = new SemillaEntidad(entidad, Vector(posXEnNivel, 0));
		// Esto se hace para que no queden parte fuera de la pantalla. Probablemente sólo para la primer entrega.
		if (campo->getAlto() < entidad->getPosicion().getY() + entidad->getAlto() ) {
			i--;
			continue;
		}

		semillasEntidades.push_back(semillaEntidad);
	}
}

void Nivel::crearNEnemigo2(int n) {
	for (int i = 0; i < n; i++) {
		int posInicialX = campo->getAncho();
		int posY = std::rand() % alto;
		// !!!! acomodar esto:
		int posXEnNivel = std::rand() % 600 + campo->getAncho();
		int velocidadX = campo->getVelocidadX();

		Entidad* entidad = new Enemigo2(posInicialX, posY, velocidadX);
		SemillaEntidad* semillaEntidad = new SemillaEntidad(entidad, Vector(posXEnNivel, 0));
		// Esto se hace para que no queden parte fuera de la pantalla. Probablemente sólo para la primer entrega.
		if (campo->getAlto() < entidad->getPosicion().getY() + entidad->getAlto() ) {
			i--;
			continue;
		}

		semillasEntidades.push_back(semillaEntidad);
	}
}

CampoMovil* Nivel::crearCampo(Configuracion* config, Jugador* jugador) {
	int inicioCampoEnEjeY = HUD_ALTO;
	CampoMovil* campo = new CampoMovil(jugador, config->getAnchoPantalla(), config->getAltoPantalla() - inicioCampoEnEjeY, inicioCampoEnEjeY);

	FondoVista* fondo;
	Json::Value fondosAPresentar = config->getRecursos("1");

	for(Json::Value f : fondosAPresentar) {
		fondo = campo->nuevoFondo(f["archivo"].asString(), 0,0, f["velocidad"].asFloat());
	}

	l.info("Se creo correctamente el nivel 1 (Parallax)");
	return campo;
}

void Nivel::plantarSemillasEnCampo() {
	list<SemillaEntidad*> nuevasSemillasEntidades;

	while (!semillasEntidades.empty()) {
		SemillaEntidad* semillaEntidad = semillasEntidades.front();
		semillasEntidades.pop_front();

		int posXEnemigo = semillaEntidad->getPosicion().getX();
		int posicionXVentana = campo->getPosicion().getX() + campo->getAncho();

		if (posicionXVentana < posXEnemigo) {
			nuevasSemillasEntidades.push_back(semillaEntidad);
		} else {
			Entidad* entidad = semillaEntidad->getEntidad();
			campo->agregarEntidad(entidad);
		}
	}

	semillasEntidades = nuevasSemillasEntidades;
}
