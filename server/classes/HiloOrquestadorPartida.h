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
    HiloOrquestadorPartida(Configuracion* config, std::list<HiloConexionServidor*>* hilosConexionesServidores);
	void run() override;
    std::list<HiloConexionServidor *> *crearHilosConexionesServidores(std::list<ConexionServidor *> *conexiones);

private:
    Configuracion* config;
    Partida *partida;
    std::list<HiloConexionServidor*>* hilosConexionesServidores;
};


#endif //CUCURUCHO_HILOORQUESTADORPARTIDA_H
