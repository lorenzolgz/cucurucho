#ifndef CUCURUCHO_HILOORQUESTADORPARTIDA_H
#define CUCURUCHO_HILOORQUESTADORPARTIDA_H


#include "../../commons/Thread.h"
#include "../../commons/connections/ConexionServidor.h"
#include "config/Configuracion.h"
#include "model/Partida.h"

class HiloOrquestadorPartida : public Thread {
public:
	HiloOrquestadorPartida(Configuracion* config, std::list<ConexionServidor*>* conexiones);
	void run() override;

private:
	Configuracion* config;
	std::list<ConexionServidor*>* conexiones;
	Partida *partida;
};


#endif //CUCURUCHO_HILOORQUESTADORPARTIDA_H
