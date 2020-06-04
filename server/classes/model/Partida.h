#ifndef CUCURUCHO_PARTIDA_H
#define CUCURUCHO_PARTIDA_H


#include "ManagerNiveles.h"
#define FIN_ARCH '\0'

class Partida {
public:
	Partida(Configuracion* config);

	void tick(struct Comando command);
	EstadoInternoNivel state();

    void setNextNivel(InformacionNivel *informacionNivel);
    bool terminoNivelActual();

    bool pasajeDeNivel();

    bool estadoJuego();

private:
	int nuevoNivel;
	Jugador* jugador;
	ManagerNiveles* managerNiveles;
    std::list<NivelConfiguracion *> nivelesPartida;

};


#endif //CUCURUCHO_PARTIDA_H
