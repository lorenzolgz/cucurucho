//
// Created by lorenzo on 6/21/20.
//

#ifndef CUCURUCHO_HILOACEPTADORCONEXIONES_H
#define CUCURUCHO_HILOACEPTADORCONEXIONES_H

#include "../../commons/Thread.h"
#include "../../commons/connections/ConexionServidor.h"
#include "../../commons/connections/AceptadorConexiones.h"
#include "../../commons/connections/ControladorDeSesiones.h"
#include "../../commons/connections/ConexionExcepcion.h"
#include "HiloOrquestadorPartida.h"
#include "HiloConexionServidor.h"
#include "../../commons/utils/Log.h"
#include <list>

class HiloAceptadorConexiones : public Thread {
public:
    HiloAceptadorConexiones(int puerto, Configuracion *config);

    void run() override;

private:
	Configuracion* config;
	std::list<HiloConexionServidor*>* hilosConexionesServidores;
	AceptadorConexiones* aceptadorConexiones;

    void notificarEstadoConexion(list<ConexionServidor *> *conexionesServidores, int estadoLogin);
    std::list<HiloConexionServidor*>* crearHilosConexionesServidores(list<ConexionServidor*>* conexionesServidores);
	void atenderPosiblesReconexiones(HiloOrquestadorPartida* hiloOrquestadorPartida);
	std::list<ConexionServidor*>* extraerConexionesDeHilosConexionesServidores();
};



#endif //CUCURUCHO_HILOACEPTADORCONEXIONES_H
