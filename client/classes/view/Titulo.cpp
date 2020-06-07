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
    l->info("La pantalla incial fue creada correctamente.");
}


void Titulo::leerInput(std::string input) {
    std::string* campoActivo = &username;
    if (!seleccionadoUsuario) {
        campoActivo = &password;
    }

    for (char c : input) {
        if (campoActivo->size() < 15 && ((c > 32 && c < 127) || (c == 32 && contador > 15))) {
            *campoActivo += c;
        } else if (!campoActivo->empty() && (c == 8 || c == 127)) {
            campoActivo->pop_back();
        } else if (c == 9 || c == 10 || (c == 11 && contador > 15)) {
            if (!seleccionadoUsuario && c == 11) estado = TITULO_VALIDAR;
            seleccionadoUsuario = !seleccionadoUsuario;
        } else if (c == 12) {   // Ctrl + D: Autoautenticar!
            estado = TITULO_VALIDAR;
            username = "cami";
            password = "1234";
            inicioTimeout = -30;
        }
    }
}


bool Titulo::validarLogin(ConexionCliente *pCliente) {
    Login credenciales;
    strcpy(credenciales.usuario, username.c_str());
    strcpy(credenciales.contrasenia, password.c_str());
    pCliente->enviarDatosDeLogin(&credenciales);
    return pCliente->contraseniaCorrecta();
}


// Devuelve un booleano indicando si el cliente debe reconectarse al servidor
bool Titulo::tick(std::string input, ConexionCliente *pCliente) {
    tituloVista->render(estado, username, password, seleccionadoUsuario);
    leerInput(input);
    bool reconectar = false;

    if (estado == TITULO_VALIDAR) {
        if (!validarLogin(pCliente)) {
            estado = TITULO_ERROR_AUTENTICACION;
            reconectar = true;
        } else {
            contador = 0;
            estado = TITULO_ACEPTADO;
        }
    }
    if (activada) contador++;

    return reconectar;
}

bool Titulo::isActivada(bool enter) {
    if (enter && !activada) {
        activada = true;
        estado = TITULO_INGRESAR;
        seleccionadoUsuario = true;
        l->info("Comenzando juego en " + std::to_string(INICIO_TIMEOUT / 60) + " segundos");
    }
    return estado == TITULO_ACEPTADO && contador > inicioTimeout;
}