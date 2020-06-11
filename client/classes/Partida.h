//
// Created by camix on 10/6/20.
//

#ifndef CUCURUCHO_PARTIDA_H
#define CUCURUCHO_PARTIDA_H

#include <SDL_types.h>
#include <SDL_system.h>
#include "../../commons/protocols/protocolo.h"
#include "../../commons/connections/ConexionCliente.h"
#include "ManagerJuego.h"
#include "../../commons/connections/IniciadorComunicacion.h"
#include "view/Titulo.h"
#include "../../commons/utils/Constantes.h"
#include "../../commons/connections/IniciadorComunicacion.h"
#include "HiloConexionCliente.h"
#include "GraphicRenderer.h"
#include "view/Titulo.h"
#include "view/ManagerVista.h"
#include "ManagerJuego.h"

#define MAX_COLA 5

class Partida {
public:
    Partida();

    void play();

    void cerrar();

private:
    ConexionCliente* conexionCliente;
    int nroJugador;

    ConexionCliente *conexionLoop(const Uint8 *currentKeyStates);

    bool pantallaInicioLoop(IniciadorComunicacion *iniciadorComunicacion,
                            Titulo *pantallaPrincipal, std::string inputText, const Uint8 *currentKeyStates);

    bool eventLoop(std::string *inputText);

    bool renderLoop(ManagerJuego *manager);
};


#endif //CUCURUCHO_PARTIDA_H
