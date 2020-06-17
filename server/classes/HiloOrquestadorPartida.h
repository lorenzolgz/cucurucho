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
	HiloOrquestadorPartida(Configuracion* config, std::list<ConexionServidor*>* conexiones, AceptadorConexiones* aceptadorDeConexiones);
	void run() override;

private:
	Configuracion* config;
	std::list<ConexionServidor*>* conexiones;
	Partida *partida;
	AceptadorConexiones* aceptadorConexiones;
    std::list<HiloConexionServidor *> *crearHilosConexionesServidores(std::list<ConexionServidor *> *conexiones);
};


#endif //CUCURUCHO_HILOORQUESTADORPARTIDA_H
