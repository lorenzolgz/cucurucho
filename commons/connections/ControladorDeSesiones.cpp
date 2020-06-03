//
// Created by ailen-magali on 3/6/20.
//

#include "ControladorDeSesiones.h"


ControladorDeSesiones::ControladorDeSesiones(ConexionServidor* conexionServidor){
    this->servidor = conexionServidor;
}

void ControladorDeSesiones::iniciarSesion(){

    //1. TODO pedirle un usuario y contraseña al cliente
    string usuario, contrasenia;

    //2. TODO guarda los datos en el json
    //3. si el user_id ya existe, verificar que la contraseña sea correcta
    //si el user no está registrado, se cerrará la conexión y se lo eliminará del json

    if(!datosCorrectos(usuario, contrasenia)) {
        //volver a pedir
        string usuarioNuevo, contraseniaNueva;
        bool sonCorrectos;
        sonCorrectos = datosCorrectos(usuarioNuevo, contraseniaNueva);
        if (!sonCorrectos) {
            //se le informa al cliente que no se le permitirá jugar
            this->servidor->cerrarConexion();
        }
    }
}

bool ControladorDeSesiones::datosCorrectos(string usuario, string contrasenia){
    bool correcta = true;

    /*
     * chequear en el json si el usuario ya existe y si la contraseña es la correcta (ver el tema de los intentos con la pass)
     */

    return correcta;
}

