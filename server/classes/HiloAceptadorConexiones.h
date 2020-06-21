//
// Created by lorenzo on 6/21/20.
//

#ifndef CUCURUCHO_HILOACEPTADORCONEXIONES_H
#define CUCURUCHO_HILOACEPTADORCONEXIONES_H

#include "../../commons/Thread.h"
#include "../../commons/connections/ConexionServidor.h"
#include "../../commons/connections/AceptadorConexiones.h"
#include "../../commons/connections/ControladorDeSesiones.h"
#include "HiloConexionServidor.h"
#include "../../commons/utils/Log.h"
#include <list>

class HiloAceptadorConexiones : public Thread {
public:

    HiloAceptadorConexiones(std::list<ConexionServidor *> *conexiones,
                            std::list<HiloConexionServidor *> *hiloConexiones,
                            AceptadorConexiones* aceptadorConexiones);

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
};



#endif //CUCURUCHO_HILOACEPTADORCONEXIONES_H
