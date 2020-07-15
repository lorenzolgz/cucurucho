#include <algorithm>
#include "Nivel.h"
#include "Enemigo2.h"
#include "Enemigo1.h"
#include "Jugador.h"
#include <list>
#include "EnemigoFinal1.h"
#include "../../../commons/utils/Constantes.h"

Nivel::Nivel(NivelConfiguracion* nivelConfig, std::map<int, Jugador*>* jugadores) {
	this->velocidad = nivelConfig->getVelocidad();
	this->largo = nivelConfig->getLargo();
	this->campo = crearCampo(jugadores);
    this->alto = campo->getAlto();
    this->jugadores = jugadores;

	if (nivelConfig->getEnemigos()->isFinal()) {
		this->extensionNivel = new ExtensionNivel(campo, jugadores);
	} else {
		this->extensionNivel = nullptr;
	}
}

void Nivel::tick() {
    campo->tick();
    if (extensionNivel != nullptr) extensionNivel->tick();
	plantarSemillasEnCampo();
}

bool Nivel::termino() {
	bool terminoBase = terminoNivelBase();
	if (terminoBase && extensionNivel != nullptr && !extensionNivel->isIniciado()) {
		extensionNivel->iniciar();
	}

	bool terminoExtension = extensionNivel == nullptr ? true : extensionNivel->termino();

	bool termino = terminoBase && terminoExtension;

	if (termino) {
		l->debug("Fin de nivel.");
		for(int i=0; i<this->jugadores->size(); i++){
		    this->jugadores->at(i)->finNivel();
		}
	}

	return termino;
}

bool Nivel::terminoNivelBase() {
	bool verificacionPosicion = campo->verificarPosicionNivel();
	if (verificacionPosicion) {
		l->debug("Fin de nivel base.");
	}

	return verificacionPosicion;
}


void Nivel::crearEnemigos(int cantClase1, int cantClase2) {
	crearEnemigosDeClase(2, cantClase2);
	crearEnemigosDeClase(1, cantClase1);
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
            case 1: {entidad = new Enemigo1(campo->getAncho(), posY, velocidadX, jugadores, campo);}
            break;
            case 2: {entidad = new Enemigo2(campo->getAncho(), posY, velocidadX, jugadores, campo);}
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
