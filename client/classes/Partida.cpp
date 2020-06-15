//
// Created by camix on 10/6/20.
//
#include "Partida.h"
#include "GestorSDL.h"

Partida::Partida() {}

void Partida::play(const char* ip_address, int port) {
    bool quit = false;

    pantallaPrincipal = new Titulo(PANTALLA_ANCHO, PANTALLA_ALTO);
    manager = new ManagerJuego();
    validarLogin = false;

    bool primeraVez = true;

    iniciadorComunicacion = new IniciadorComunicacion(ip_address, port);
    colaMensajes = new ColaBloqueante<nlohmann::json>();
    estadoLogin.nroJugador = LOGIN_PENDIENTE;

    hiloConexionCliente = nullptr;
    l->info("Los objetos fueron inicializados correctamente a partir de los datos de la configuracion inicial");

    while (!quit) {
        try{

            const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);

            if(currentKeyStates[SDL_SCANCODE_LCTRL] && currentKeyStates[SDL_SCANCODE_X] && primeraVez){
                std::cout << "Apretaste CTRL+X \n";
                primeraVez = false;
                conexionCliente->cerrar();
            }

            SDL_RenderClear(GraphicRenderer::getInstance());

            std::string inputText;
            quit = quit || eventLoop(&inputText);

            if (estadoLogin.nroJugador <= 0 && validarLogin) {
                autenticarServidor();
                validarLogin = false;
            }

            // TODO: Separar mejor el logueo conexion del logueo vista
            if (pantallaInicioLoop(inputText, currentKeyStates)) {
                continue;
            }

            // TODO patch para race conditions
            if (hiloConexionCliente == nullptr) {
                std::cout << "Creando un nuevo hiloConexionCliente\n";
                hiloConexionCliente = new HiloConexionCliente(conexionCliente, colaMensajes);
                hiloConexionCliente->start();
            }

            if (!colaMensajes->empty()) {
                // !!!!! reducir MAX_COLA
                // colaMensajes->pop(MAX_COLA);
                while (colaMensajes->size() > MAX_COLA_CLIENTE){
                    colaMensajes->pop();
                    l->info("Se desencola debido a la alta cantidad de mensajes en la cola");
                }

                nlohmann::json instruccion = colaMensajes->pop();
                manager->estadoNivel(instruccion);
            }

            conexionLoop(currentKeyStates);
            quit = quit || renderLoop();
        }
        catch(...){ // ConexionExcepcion
            std::cout << "Ocurrio una excepcion\n";
            std::cout << ".:. Reconectando .:.\n";
            conexionCliente = iniciadorComunicacion->conectar();
            while(conexionCliente == nullptr){
                std::cout << ".:. Reconectando .:.\n";
            }
            std::cout << "Ya reconecte!\n";
            hiloConexionCliente = nullptr;
            //hiloConexionCliente->conexionCliente = conexionCliente;
            std::cout << "Cambie conexionCliente del hiloConexionCliente\n";

        }
    }

}


void Partida::autenticarServidor() {
    Login credenciales;
    conexionCliente = iniciadorComunicacion->conectar();

    if (conexionCliente == nullptr) {
        estadoLogin.nroJugador = LOGIN_SIN_CONEXION;
        return;
    }

    pantallaPrincipal->getCredenciales(&credenciales);
    conexionCliente->enviarDatosDeLogin(&credenciales);
    estadoLogin = conexionCliente->recibirEstadoLogin();
    l->info("EstadoLogin enviado por el conexionServidor: " + std::to_string(estadoLogin.nroJugador));

    if (estadoLogin.nroJugador < 0) {
        conexionCliente->cerrar();
    }

    manager->setEstadoLogin(estadoLogin);
}

void Partida::cerrar() {
    if (conexionCliente != nullptr) {
        conexionCliente->cerrar();
    }
}

// Manejar eventos (teclas, texto) de SDL
// Si se cumple `SDL_QUIT`, devuelve true.
bool Partida::eventLoop(std::string* inputText) {
    GestorSDL* gestorSDL;
    return gestorSDL->event(inputText);
}


bool Partida::pantallaInicioLoop(std::string inputText, const Uint8 *currentKeyStates) {

    // El usuario presiona ENTER o INTRO o ESPACIO
    bool onStart = currentKeyStates[SDL_SCANCODE_KP_ENTER] || currentKeyStates[SDL_SCANCODE_RETURN] || currentKeyStates[SDL_SCANCODE_SPACE];

    if (!pantallaPrincipal->estaActivada(onStart, estadoLogin.nroJugador)) {
    	pantallaPrincipal->tick(inputText, estadoLogin.nroJugador, &validarLogin);
		SDL_RenderPresent(GraphicRenderer::getInstance());
        return true;
    }

    return false;
}

// Comunicacion con el cliente. Envia la secuencia de teclas presionada
void Partida::conexionLoop(const Uint8 *currentKeyStates) {

    if (!manager->enJuego()) return;

    struct Comando client_command = {false, false, false, false};

    // TODO: estadoLogin esta repetido e inconsistente
	client_command.nroJugador = manager->getEstadoLogin().nroJugador;
	client_command.arriba = currentKeyStates[SDL_SCANCODE_UP];
    client_command.abajo = currentKeyStates[SDL_SCANCODE_DOWN];
    client_command.izquierda = currentKeyStates[SDL_SCANCODE_LEFT];
    client_command.derecha = currentKeyStates[SDL_SCANCODE_RIGHT];

    // Send data (command)
    conexionCliente->enviarComando(&client_command);
}

// Renderiza el juego. Devuelve `false` si llego al nivel final (para salir del juego)
// TODO: Hardcodeadisimo. Cambiar.
bool Partida::renderLoop() {

    bool quit = false;

    manager->render();
    quit = quit || manager->terminoJuego();
    SDL_RenderPresent(GraphicRenderer::getInstance());

    return quit;
}