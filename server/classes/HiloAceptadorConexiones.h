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


    HiloAceptadorConexiones(
            int puerto,
            Configuracion *config);

    void reinstanciarListaConexiones(std::list<ConexionServidor*>* conexiones,
                                     std::list<HiloConexionServidor*>* hiloConexiones);

    void atenderPosiblesReconexiones(std::list<ConexionServidor *> *conexiones,
                                     std::list<HiloConexionServidor *> *hiloConexiones,
                                     AceptadorConexiones* aceptadorConexiones);

    void run() override;

private:
    std::list<ConexionServidor*>* conexiones;
    std::list<HiloConexionServidor*>* hiloConexiones;
    AceptadorConexiones* aceptadorConexiones;
    Configuracion* config;
    int puerto;

    void notificarEstadoConexion(list<ConexionServidor *> *conexiones, int estadoLogin);

    list<HiloConexionServidor *> *
    crearHilosConexionesServidores(list<ConexionServidor *> *conexiones, AceptadorConexiones *aceptadorConexiones);
};



#endif //CUCURUCHO_HILOACEPTADORCONEXIONES_H
