//
// Created by camix on 10/6/20.
//
#include "Partida.h"
#include "GestorSDL.h"

Partida::Partida() {}

void Partida::play() {
    bool quit = false;

    Titulo* pantallaPrincipal = new Titulo(PANTALLA_ANCHO, PANTALLA_ALTO);
    ManagerJuego* manager = new ManagerJuego();

    char* ip_address = (char*) "127.0.0.1";
    int port = 3040;
    IniciadorComunicacion* iniciadorComunicacion = new IniciadorComunicacion(ip_address, port);
    Partida::conexionCliente = iniciadorComunicacion->conectar();
    auto* colaComandos = new ColaBloqueante<nlohmann::json>();
    HiloConexionCliente* hiloConexionCliente = nullptr;
    l->info("Los objetos fueron inicializados correctamente a partir de los datos de la configuracion inicial");

    while (!quit) {
        const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
        SDL_RenderClear(GraphicRenderer::getInstance());

        std::string inputText;
        quit = quit || eventLoop(&inputText);

        // TODO: Separar mejor el logueo conexion del logueo vista
        if (pantallaInicioLoop(iniciadorComunicacion, &conexionCliente, pantallaPrincipal, inputText, currentKeyStates)) {
            continue;
        }

        // !!!! TODO javi
        if (hiloConexionCliente == nullptr) {
            hiloConexionCliente = new HiloConexionCliente(conexionCliente, colaComandos);
            hiloConexionCliente->start();
        }

        if (!colaComandos->empty()) {
            // TODO no es mejor primero vaciar y despues imprimir?
            nlohmann::json instruccion = colaComandos->pop();
            manager->estadoNivel(instruccion);
            while (colaComandos->size() > MAX_COLA){
                colaComandos->pop();
                l->info("Se desencola debido a la alta cantidad de comandos en la cola");
            }
        }

        if (!conexionLoop(conexionCliente, currentKeyStates)) {
            continue;
        }

        quit = quit || renderLoop(manager,conexionCliente);
    }

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

// Muestra la pantalla de logueo
// En el caso que se haya rechazado la conexion, se vuelve a establecer
bool Partida::pantallaInicioLoop(IniciadorComunicacion* iniciadorComunicacion, ConexionCliente** conexionCliente,
                        Titulo *pantallaPrincipal, std::string inputText, const Uint8 *currentKeyStates) {

    // El usuario presiona ENTER o INTRO o ESPACIO
    bool onStart = currentKeyStates[SDL_SCANCODE_KP_ENTER] || currentKeyStates[SDL_SCANCODE_RETURN] || currentKeyStates[SDL_SCANCODE_SPACE];

    if (!pantallaPrincipal->isActivada(onStart)) {
        if (pantallaPrincipal->tick(inputText, *conexionCliente)) {
            (*conexionCliente)->cerrar();
            *conexionCliente = iniciadorComunicacion->conectar();
        }
        SDL_RenderPresent(GraphicRenderer::getInstance());
        return true;
    }

    return false;
}

// Comunicacion con el cliente. Envia la secuencia de teclas presionada
ConexionCliente* Partida::conexionLoop(ConexionCliente* conexionCliente, const Uint8 *currentKeyStates) {

    struct Comando client_command = {false, false, false, false};

    client_command.arriba = currentKeyStates[SDL_SCANCODE_UP];
    client_command.abajo = currentKeyStates[SDL_SCANCODE_DOWN];
    client_command.izquierda = currentKeyStates[SDL_SCANCODE_LEFT];
    client_command.derecha = currentKeyStates[SDL_SCANCODE_RIGHT];

    // Send data (command)
    conexionCliente->enviarComando(&client_command);

    return conexionCliente;
}

// Renderiza el juego. Devuelve `false` si llego al nivel final (para salir del juego)
// TODO: Hardcodeadisimo. Cambiar.
bool Partida::renderLoop(ManagerJuego* manager, ConexionCliente* conexionCliente) {

    bool quit = false;

    manager->setInformacionNivel();
    quit = quit || manager->terminoJuego();
    SDL_RenderPresent(GraphicRenderer::getInstance());

    return quit;
}