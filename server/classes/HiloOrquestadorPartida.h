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
};


#endif //CUCURUCHO_HILOORQUESTADORPARTIDA_H
