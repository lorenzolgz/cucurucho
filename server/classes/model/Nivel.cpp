#include <algorithm>
#include "Nivel.h"
#include "Enemigo2.h"
#include "Enemigo1.h"
#include "Jugador.h"
#include "../../../commons/utils/Log.h"
#include "../states/EstadoInternoNivel.h"
#include <queue>
#include <iterator>
#include <list>
#include "../../../commons/utils/Constantes.h"

#define CAMPO_ANCHO 960
#define CAMPO_ALTO 576

Nivel::Nivel(NivelConfiguracion* nivelConfig, std::map<int, Jugador*>* jugadores) {
	this->velocidad = nivelConfig->getVelocidad();
	this->largo = nivelConfig->getLargo();
	this->campo = crearCampo(jugadores);
    this->alto = campo->getAlto();
    this->jugadores = jugadores;
}

void Nivel::tick() {
    campo->tick();
	plantarSemillasEnCampo();
}

bool Nivel::termino() {
	bool verificacionPosicion = campo->verificarPosicionNivel();
	if (verificacionPosicion) {
		l->debug("Fin de nivel.");
	}

	return verificacionPosicion;
}

void Nivel::crearEnemigos(int cantClase1, int cantClase2) {
	crearEnemigosDeClase(2, cantClase2);
	crearEnemigosDeClase(1, cantClase1);
	// !!!!!
	EntidadEnemigo* entidad = new EnemigoFinal1(campo->getAncho(), 200, campo->getVelocidadX(), jugadores);
	SemillaEntidad* semillaEntidad = new SemillaEntidad(entidad, Vector(campo->getAncho() + 100, 0));
	semillasEntidades.push_back(semillaEntidad);
}

void Nivel::crearEnemigosDeClase(int tipoDeEnemigo, int cantDeEnemigos){
    for (int i = 0; i < cantDeEnemigos; i++) {
        int posXBase = campo->getAncho();
        int posY = std::rand() % alto;

        int rangoEnemigos = (int) largo - posXBase;
        if (rangoEnemigos <= 0) {
            l->info("Ancho de pantalla mas grande que largo del nivel");
            rangoEnemigos = largo;
        }
        int posXEnNivel = std::rand() % rangoEnemigos + posXBase;
        float velocidadX = campo->getVelocidadX();

        Entidad* entidad;

        switch (tipoDeEnemigo) {
            case 1: {entidad = new Enemigo1(posXEnNivel, posY, velocidadX, jugadores);}
            break;
            case 2: {entidad = new Enemigo2(posXEnNivel, posY, velocidadX, jugadores);}
            break;
            // Todo después vemos
            default: {entidad = nullptr;};
        }

        SemillaEntidad* semillaEntidad = new SemillaEntidad(entidad, Vector(posXEnNivel, 0));
        // Esto se hace para que no queden parte fuera de la pantalla. Probablemente sólo para la primer entrega.
        if (campo->getAlto() < entidad->getPosicion().getY() + entidad->getAlto()) {
            i--;
            continue;
        }

        semillasEntidades.push_back(semillaEntidad);
    }
}

CampoMovil* Nivel::crearCampo(std::map<int, Jugador*>* jugadores) {
	auto* campo = new CampoMovil(jugadores, CAMPO_ANCHO, CAMPO_ALTO, velocidad, largo);

	l->info("Se creo correctamente el nivel (Parallax)");
	return campo;
}

void Nivel::plantarSemillasEnCampo() {
	std::list<SemillaEntidad*> nuevasSemillasEntidades;

	while (!semillasEntidades.empty()) {
		SemillaEntidad* semillaEntidad = semillasEntidades.front();
		semillasEntidades.pop_front();

		int posXSemillaEnemigo = semillaEntidad->getPosicion().getX();
		int posXCampoEnNivel = campo->getPosicion().getX() + campo->getAncho();

		if (posXCampoEnNivel < posXSemillaEnemigo) {
			nuevasSemillasEntidades.push_back(semillaEntidad);
		} else {
			Entidad* entidad = semillaEntidad->getEntidad();
			// TODO este casteo es pa quilombo!!!!
			campo->agregarEntidadEnemigo((EntidadEnemigo*) entidad);
		}
	}

	semillasEntidades = nuevasSemillasEntidades;
}

EstadoInternoCampoMovil Nivel::state() {
	return campo->state();
}

void Nivel::nuevoDisparo(Disparo *pDisparo) {
    this->campo->nuevoDisparo(pDisparo);
}
