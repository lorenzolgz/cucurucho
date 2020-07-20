#ifndef CUCURUCHO_HILOORQUESTADORPARTIDA_H
#define CUCURUCHO_HILOORQUESTADORPARTIDA_H


#include "../../commons/Thread.h"
#include "../../commons/connections/ConexionServidor.h"
#include "config/Configuracion.h"
#include "model/Partida.h"
#include "../../commons/connections/AceptadorConexiones.h"
#include "HiloConexionServidor.h"

class HiloOrquestadorPartida : public Thread {
public:
    HiloOrquestadorPartida(Configuracion* config, std::list<HiloConexionServidor*>* hilosConexionesServidores, AceptadorConexiones* aceptadorConexiones);
	void run() override;
	bool termino();

private:
    Partida *partida;
    std::list<HiloConexionServidor*>* hilosConexionesServidores;
	AceptadorConexiones* aceptadorConexiones;
	bool quit;
	int ticksGameOver;
    Configuracion *config;

	bool processData(Partida *partida, Comando *comandos, EstadoTick *estadoTick, InformacionNivel *informacionNivel,
					 std::list<HiloConexionServidor *> *conexiones, int *nuevoNivel);
};


#endif //CUCURUCHO_HILOORQUESTADORPARTIDA_H
