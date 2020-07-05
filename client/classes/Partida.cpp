//
// Created by camix on 10/6/20.
//
#include "Partida.h"
#include "GestorSDL.h"
#include "../../commons/connections/ConexionExcepcion.h"

Partida::Partida() {}

void Partida::play(Configuracion* configuracion, const char* ip_address, int port, bool conexionPerdida) {
    bool quit = false;

    pantallaPrincipal = new Titulo(PANTALLA_ANCHO, PANTALLA_ALTO, conexionPerdida);
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

            hacks(currentKeyStates);

            SDL_RenderClear(GraphicRenderer::getInstance());

            std::string inputText;
            quit = quit || eventLoop(&inputText);

            if (!colaMensajes->empty()) {
                while (colaMensajes->size() > configuracion->getMaxCola()){
                    nlohmann::json json = colaMensajes->pop();
                    // Solo se deberian matar los mensajes de ESTADO_TICK que no indican fin del juego
                    // TODO: quiero llorar
                    if (json["tipoMensaje"] != ESTADO_TICK || json["numeroNivel"] == FIN_DE_JUEGO) {
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

            if (estadoLogin.estadoLogin <= 0 && validarLogin) {
                autenticarServidor();
            }

            pantallaInicioLoop(inputText, currentKeyStates);

            conexionLoop(currentKeyStates);

            renderLoop();

            quit = quit || manager->terminoJuego();
        }

    } catch (std::exception& exc) {

        // TODO: Parche para cuando no se cierra el cliente cuando termina el juego
        // Contempla los casos donde el cliente pierde la conexion al enviar un comando
        if (hiloConexionCliente->isActivo()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
            hiloConexionCliente->cerrarConexion();
        }

        while(!colaMensajes->empty()) {
            nlohmann::json instruccion = colaMensajes->pop();
            l->debug("ERROR DE CONEXION: desencolando " + instruccion.dump());
            if (instruccion["tipoMensaje"] == ESTADO_TICK) setEstadoTick(instruccion);
        }

        if (manager->terminoJuego()) {
            renderLoop();
            l->info("Finalizo el juego.");
        } else {
            l->error("Se interrumpio el juego: " + std::string(exc.what()));
            l->error("Reiniciando...");
            reiniciarInstanciaHilo();
            play(configuracion, ip_address, port, true);
            return;
        }
    }

    hiloConexionCliente->cerrarConexion();

}


void Partida::autenticarServidor() {
    Login credenciales;

    if (estadoLogin.estadoLogin != LOGIN_ESPERANDO_RESPUESTA && !hiloConexionCliente->isActivo()) {
        comenzarHilo();
        estadoLogin.estadoLogin = LOGIN_ESPERANDO_RESPUESTA;
        return;
    }

    if (hiloConexionCliente->conexionCliente == nullptr) {
        if (!hiloConexionCliente->isActivo()) {
            estadoLogin.estadoLogin = LOGIN_SIN_CONEXION;
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
        estadoLogin.estadoLogin = LOGIN_SIN_CONEXION;
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

    pantallaPrincipal->tick(inputText, estadoLogin.estadoLogin, &validarLogin);
	SDL_RenderPresent(GraphicRenderer::getInstance());
}

// Comunicacion con el cliente. Envia la secuencia de teclas presionada
void Partida::conexionLoop(const Uint8 *currentKeyStates) {

    if (estadoLogin.nroJugador > 0 && !hiloConexionCliente->isActivo()) {
        throw ConexionExcepcion();
    }

    if (!manager->enJuego() || estadoLogin.nroJugador < 0) return;

    struct Comando client_command = {false, false, false, false, false, false};

	client_command.nroJugador = estadoLogin.nroJugador;
	client_command.arriba = currentKeyStates[SDL_SCANCODE_UP];
    client_command.abajo = currentKeyStates[SDL_SCANCODE_DOWN];
    client_command.izquierda = currentKeyStates[SDL_SCANCODE_LEFT];
    client_command.derecha = currentKeyStates[SDL_SCANCODE_RIGHT];
    client_command.disparo = currentKeyStates[SDL_SCANCODE_SPACE];

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


void Partida::hacks(const Uint8 *currentKeyStates) {
    if (currentKeyStates[SDL_SCANCODE_LCTRL] && currentKeyStates[SDL_SCANCODE_X]){
        l->info("Apretaste CTRL+X. Cerrando conexion de cliente"); // TODO: dejar log? seee aguanten los logs vieja no me importa nada
        hiloConexionCliente->cerrarConexion();
    }

    if (currentKeyStates[SDL_SCANCODE_LCTRL] && currentKeyStates[SDL_SCANCODE_P]){
        SDL_Delay(1000);
    }

    if (currentKeyStates[SDL_SCANCODE_LCTRL] && currentKeyStates[SDL_SCANCODE_D]){
        pantallaPrincipal->setAutoCompletar();
    }
}


void Partida::setEstadoTick(nlohmann::json mensaje) {
    struct EstadoTick estado;
    estado.nuevoNivel = mensaje["nuevoNivel"];
    estado.posX = mensaje["posX"];
    estado.numeroNivel = mensaje["numeroNivel"];

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
    for (nlohmann::json informacionJson : mensaje["estadosEnemigos"]){
        EstadoEnemigo estadoEnemigo;
        estadoEnemigo.posicionX = informacionJson["posicionX"];
        estadoEnemigo.posicionY = informacionJson["posicionY"];
        estadoEnemigo.clase = informacionJson["clase"];
        estado.estadosEnemigos.push_back(estadoEnemigo);
    }
    manager->setEstadoTick(estado);
}

void Partida::setInformacionNivel(nlohmann::json mensaje) {
    struct InformacionNivel info;
    
    info.numeroNivel = mensaje["numeroNivel"];

    info.velocidad = mensaje["velocidad"];
    strcpy(info.informacionFinNivel, std::string(mensaje["informacionFinNivel"]).c_str());
    for (nlohmann::json informacionJson : mensaje["informacionFondo"]) {
        InformacionFondo informacionFondoJson;
        informacionFondoJson.pVelocidad = informacionJson["velocidad"];
        strcpy(informacionFondoJson.pFondo, std::string(informacionJson["fondo"]).c_str());
        info.informacionFondo.push_back(informacionFondoJson);
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
        pantallaPrincipal->reiniciarPassword();
    } else {
        validarLogin = false;
    }
    Partida::estadoLogin = estadoLogin;
}