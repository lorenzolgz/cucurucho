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
#include "config/Configuracion.h"
#include "Audio.h"
#include "GestorSDL.h"

class Partida {
public:
    Partida();

    void iniciar(Configuracion* configuracion, const char *ip_address, int port, bool conexionPerdida = false);

private:
    Titulo* pantallaPrincipal;
    ManagerJuego* manager;
    HiloConexionCliente* hiloConexionCliente;
    IniciadorComunicacion* iniciadorComunicacion;
    ColaBloqueante<nlohmann::json>* colaMensajes;
    struct EstadoLogin estadoLogin;
    bool validarLogin;
    GestorSDL* gestorSDL;
    bool vieneDeTocarTeclaInvencible;
    bool enviarInvencible;

    void conexionLoop(const Uint8 *currentKeyStates);
    void pantallaInicioLoop(std::string inputText, const Uint8 *currentKeyStates);
    bool eventLoop(std::string *inputText);
    void renderLoop();
    void autenticarServidor();
    void comenzarHilo();
    void reiniciarInstanciaHilo();
    void hacks(const Uint8 *currentKeyStates);
    void procesarEstadoTick(nlohmann::json mensaje);
    void procesarInformacionNivel(nlohmann::json mensaje);
    void procesarEstadoLogin(nlohmann::json mensaje);
    void procesarInvencible(bool apretoTeclaInvencible);
};


#endif //CUCURUCHO_PARTIDA_H
