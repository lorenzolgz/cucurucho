//
// Created by javier on 10/5/20.
//

#include "Titulo.h"
#include "../../../commons/connections/ConexionCliente.h"
#include <string.h>
#include "../../../commons/utils/Log.h"

Titulo::Titulo(int ancho, int alto, bool conexionPerdida) {
    activada = conexionPerdida;
    contador = 0;
    Titulo::tituloVista = new TituloVista(ancho, alto, conexionPerdida);
    username = "";
    password = "";
    seleccionadoUsuario = true;
    estado = conexionPerdida ? TITULO_INGRESAR : TITULO_VACIO;
    autoCompletar = false;
    autoCompletarIndice = 0;

    Audio *audio1 = Audio::getInstante();
    audioInicioPartida = audio1->generarSoundEffect("sfx-29.wav");
    Audio *audio2 = Audio::getInstante();
    audioErrorUsuario = audio2->generarSoundEffect("sfx-30.wav");


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

void Titulo::estaActivada(bool enter) {
    if (enter && !activada) {
        activada = true;
        estado = TITULO_INGRESAR;
        seleccionadoUsuario = true;


        audioInicioPartida->play(200);
        l->info("Pantalla de inicio activada.");
    }
}


void Titulo::getCredenciales(struct Login* credenciales) {
    if (!autoCompletar) {
        strcpy(credenciales->usuario, username.c_str());
        strcpy(credenciales->contrasenia, password.c_str());
    } else {
        strcpy(credenciales->usuario, autoCredenciales[autoCompletarIndice % 5].usuario);
        strcpy(credenciales->contrasenia, autoCredenciales[autoCompletarIndice % 5].contrasenia);
        autoCompletarIndice++;
    }
}

void Titulo::setAutoCompletar() {
    autoCompletar = true;
}

void Titulo::reiniciarPassword() {
    audioErrorUsuario->play(200);
    password = "";
}
