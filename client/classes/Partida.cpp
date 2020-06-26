//
// Created by camix on 10/6/20.
//
#include "Partida.h"
#include "GestorSDL.h"
#include "../../commons/connections/ConexionExcepcion.h"

Partida::Partida() {}

void Partida::play(const char* ip_address, int port) {
    bool quit = false;

    pantallaPrincipal = new Titulo(PANTALLA_ANCHO, PANTALLA_ALTO);
    manager = new ManagerJuego();
    estadoLogin = {LOGIN_PENDIENTE};
    validarLogin = false;

    colaMensajes = new ColaBloqueante<nlohmann::json>();
    estadoLogin.nroJugador = LOGIN_PENDIENTE;
    iniciadorComunicacion = new IniciadorComunicacion(ip_address, port);
    hiloConexionCliente = new HiloConexionCliente(colaMensajes, iniciadorComunicacion);

    l->info("Los objetos fueron inicializados correctamente a partir de los datos de la configuracion inicial");

    try{
        while (!quit) {

            const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

            if (currentKeyStates[SDL_SCANCODE_LCTRL] && currentKeyStates[SDL_SCANCODE_X]){
                l->info("Apretaste CTRL+X. Cerrando conexion de cliente"); // TODO: dejar log? seee aguanten los logs vieja no me importa nada
                hiloConexionCliente->cerrarConexion();
            }

            SDL_RenderClear(GraphicRenderer::getInstance());

            std::string inputText;
            quit = quit || eventLoop(&inputText);

            if (!colaMensajes->empty()) {
                while (colaMensajes->size() > MAX_COLA_CLIENTE){
                    nlohmann::json json = colaMensajes->pop();
                    // Solo se deberian matar los mensajes de ESTADO_TICK
                    if (json["tipoMensaje"] != ESTADO_TICK) {
                        colaMensajes->push_back(json);
                        break;
                    }
                    l->info("Se desencola debido a la alta cantidad de mensajes en la cola");
                }

                nlohmann::json instruccion = colaMensajes->pop();

                if (instruccion["tipoMensaje"] == INFORMACION_NIVEL) setInformacionNivel(instruccion);
                else if (instruccion["tipoMensaje"] == ESTADO_TICK) setEstadoTick(instruccion);
                else if (instruccion["tipoMensaje"] == ESTADO_LOGIN) setEstadoLogin(instruccion);
            }

            if (estadoLogin.nroJugador <= 0 && validarLogin) {
                autenticarServidor();
            }

            pantallaInicioLoop(inputText, currentKeyStates);

            conexionLoop(currentKeyStates);

            renderLoop();

            quit = quit || manager->terminoJuego();
        }
    } catch (std::exception& exc) {
        l->error("Se interrumpio el juego: " + std::string(exc.what()));
        l->error("Reiniciando...");
        reiniciarInstanciaHilo();
        play(ip_address, port);
    }

    hiloConexionCliente->cerrarConexion();

}


void Partida::autenticarServidor() {
    Login credenciales;

    if (estadoLogin.nroJugador != LOGIN_ESPERANDO_RESPUESTA && !hiloConexionCliente->isActivo()) {
        comenzarHilo();
        estadoLogin.nroJugador = LOGIN_ESPERANDO_RESPUESTA;
        return;
    }

    if (hiloConexionCliente->conexionCliente == nullptr) {
        if (!hiloConexionCliente->isActivo()) {
            estadoLogin.nroJugador = LOGIN_SIN_CONEXION;
            reiniciarInstanciaHilo();
            validarLogin = false;
        }
        return;
    }

    pantallaPrincipal->getCredenciales(&credenciales);
    try {
        hiloConexionCliente->conexionCliente->enviarDatosDeLogin(&credenciales);
        manager->setUsername(std::string(credenciales.usuario));
    } catch (std::exception& exc) {
        estadoLogin.nroJugador = LOGIN_SIN_CONEXION;
    }

    validarLogin = false;

}


// Manejar eventos (teclas, texto) de SDL
// Si se cumple `SDL_QUIT`, devuelve true.
bool Partida::eventLoop(std::string* inputText) {
    GestorSDL* gestorSDL;
    return gestorSDL->event(inputText);
}


void Partida::pantallaInicioLoop(std::string inputText, const Uint8 *currentKeyStates) {

    // El usuario presiona ENTER o INTRO o ESPACIO
    bool onStart = currentKeyStates[SDL_SCANCODE_KP_ENTER] || currentKeyStates[SDL_SCANCODE_RETURN] || currentKeyStates[SDL_SCANCODE_SPACE];

    pantallaPrincipal->estaActivada(onStart);

    if (estadoLogin.estadoLogin > 0) {
        return;
    }

    pantallaPrincipal->tick(inputText, estadoLogin.nroJugador, &validarLogin);
	SDL_RenderPresent(GraphicRenderer::getInstance());
}

// Comunicacion con el cliente. Envia la secuencia de teclas presionada
void Partida::conexionLoop(const Uint8 *currentKeyStates) {

    if (!manager->enJuego() || estadoLogin.nroJugador < 0) return;

    struct Comando client_command = {false, false, false, false};

	client_command.nroJugador = estadoLogin.nroJugador;
	client_command.arriba = currentKeyStates[SDL_SCANCODE_UP];
    client_command.abajo = currentKeyStates[SDL_SCANCODE_DOWN];
    client_command.izquierda = currentKeyStates[SDL_SCANCODE_LEFT];
    client_command.derecha = currentKeyStates[SDL_SCANCODE_RIGHT];

    // Send data (command)
    if (!hiloConexionCliente->isActivo()) {
        throw ConexionExcepcion();
    }
    hiloConexionCliente->conexionCliente->enviarComando(&client_command);
}

void Partida::renderLoop() {
    if (estadoLogin.estadoLogin <= 0) return;

    manager->render();
    SDL_RenderPresent(GraphicRenderer::getInstance());
}


void Partida::comenzarHilo() {
    hiloConexionCliente->start();
}


void Partida::reiniciarInstanciaHilo() {
    hiloConexionCliente->cerrarConexion();
    hiloConexionCliente = new HiloConexionCliente(colaMensajes, iniciadorComunicacion);
}


void Partida::setEstadoTick(nlohmann::json mensaje) {
    struct EstadoTick estado;
    estado.nuevoNivel = mensaje["numeroNivel"];
    int i = 0;
    for (; i < MAX_JUGADORES; i++ ) {
        estado.estadosJugadores[i].helper1.posicionX = mensaje["estadosJugadores"][i]["helper1"]["posicionX"];
        estado.estadosJugadores[i].helper1.posicionY = mensaje["estadosJugadores"][i]["helper1"]["posicionY"];
        estado.estadosJugadores[i].helper1.angulo = mensaje["estadosJugadores"][i]["helper1"]["angulo"];
        estado.estadosJugadores[i].helper2.posicionX = mensaje["estadosJugadores"][i]["helper2"]["posicionX"];
        estado.estadosJugadores[i].helper2.posicionY = mensaje["estadosJugadores"][i]["helper2"]["posicionY"];
        estado.estadosJugadores[i].helper2.angulo = mensaje["estadosJugadores"][i]["helper2"]["angulo"];
        estado.estadosJugadores[i].posicionX = mensaje["estadosJugadores"][i]["posicionX"];
        estado.estadosJugadores[i].posicionY = mensaje["estadosJugadores"][i]["posicionY"];
        estado.estadosJugadores[i].presente = mensaje["estadosJugadores"][i]["presente"];
    }
    int j = 0;
    for (; j < MAX_ENEMIGOS; j++ ){
        estado.estadosEnemigos[j].posicionX = mensaje["estadosEnemigos"][j]["posicionX"];
        estado.estadosEnemigos[j].posicionY = mensaje["estadosEnemigos"][j]["posicionY"];
        estado.estadosEnemigos[j].clase = mensaje["estadosEnemigos"][j]["clase"];
    }
    manager->setEstadoTick(estado);
}

void Partida::setInformacionNivel(nlohmann::json mensaje) {
    struct InformacionNivel info;

    info.numeroNivel = mensaje["numeroNivel"];
    info.velocidad = mensaje["velocidad"];
    strcpy(info.informacionFinNivel, std::string(mensaje["informacionFinNivel"]).c_str());
    for (int i = 0; i < MAX_FONDOS ; i++){
        info.informacionFondo[i].pVelocidad = mensaje["informacionFondo"][i]["velocidad"];
        strcpy(info.informacionFondo[i].pFondo, std::string(mensaje["informacionFondo"][i]["fondo"]).c_str());
    }
    manager->setInformacionNivel(info);
}

void Partida::setEstadoLogin(nlohmann::json mensaje) {
    struct EstadoLogin estadoLogin;

    estadoLogin.nroJugador = mensaje["nroJugador"];
    estadoLogin.estadoLogin = mensaje["estadoLogin"];
    estadoLogin.cantidadJugadores = mensaje["cantidadJugadores"];

    for (int i = 0; i < MAX_JUGADORES; i++) {
        strcpy(estadoLogin.jugadores[i], std::string(mensaje["jugadores"][i]).c_str());
    }

    manager->setEstadoLogin(estadoLogin);

    if (estadoLogin.estadoLogin <= 0) {
        reiniciarInstanciaHilo();
    } else {
        validarLogin = false;
    }
    Partida::estadoLogin = estadoLogin;
}
