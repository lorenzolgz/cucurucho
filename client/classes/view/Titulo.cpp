//
// Created by javier on 10/5/20.
//

#include "Titulo.h"
#include "../../../commons/connections/ConexionCliente.h"
#include <string.h>
#include "../../../commons/utils/Log.h"

Titulo::Titulo(int ancho, int alto) {
    activada = false;
    contador = 0;
    inicioTimeout = INICIO_TIMEOUT;
    Titulo::tituloVista = new TituloVista(ancho, alto);
    username = "";
    password = "";
    seleccionadoUsuario = true;
    estado = TITULO_VACIO;
    autoCompletar = false;
    autoCompletarIndice = 0;
    l->info("La pantalla incial fue creada correctamente.");
}


void Titulo::leerInput(std::string input, bool *validarLogin) {
    std::string* campoActivo = &username;
    if (!seleccionadoUsuario) {
        campoActivo = &password;
    }

    for (char c : input) {
        if (activada) {
            if (campoActivo->size() < (LARGO_USERNAME - 1) && ((c > 32 && c < 127) || (c == 32 && contador > 15))) {
                *campoActivo += c;
            } else if (!campoActivo->empty() && (c == 8 || c == 127)) {
                campoActivo->pop_back();
            } else if (c == 9 || c == 10 || (c == 11 && contador > 15)) {
                if (!seleccionadoUsuario && c == 11) *validarLogin = true;
                seleccionadoUsuario = !seleccionadoUsuario;
            }
        } else if (c == 12) {   // Ctrl + D: Autoautenticar!
            *validarLogin = true;
            autoCompletar = true;
            inicioTimeout = -30;
        }
    }
    if (autoCompletar) {
        *validarLogin = true;
    }
}


void Titulo::tick(std::string input, int estadoLogin, bool *validarLogin) {
    tituloVista->render(estado, estadoLogin, username, password, seleccionadoUsuario);
    leerInput(input, validarLogin);

    if (estado == TITULO_INGRESAR) contador++;
}

bool Titulo::estaActivada(bool enter, int estadoLogin) {
    if (enter && !activada) {
        activada = true;
        estado = TITULO_INGRESAR;
        seleccionadoUsuario = true;
        l->info("Comenzando juego en " + std::to_string(INICIO_TIMEOUT / 60) + " segundos");
    }
    return estadoLogin > 0;
}


void Titulo::getCredenciales(struct Login* credenciales) {
    if (!autoCompletar) {
        strcpy(credenciales->usuario, username.c_str());
        strcpy(credenciales->contrasenia, password.c_str());
    } else {
        strcpy(credenciales->usuario, autoCredenciales[autoCompletarIndice].usuario);
        strcpy(credenciales->contrasenia, autoCredenciales[autoCompletarIndice].contrasenia);
        autoCompletarIndice++;
    }
}