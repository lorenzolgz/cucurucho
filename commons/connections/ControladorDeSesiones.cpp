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
    //si no lo es, el usuario tendrá hasta ? intentos, sino se cerrará la conexión y se lo eliminará del json

    if(!datosCorrectos(usuario, contrasenia)){
        //volver a pedir
        string usuarioNuevo, contraseniaNueva;
        bool sonCorrectos;
        sonCorrectos = datosCorrectos(usuarioNuevo, contraseniaNueva);
        if(!sonCorrectos){
            this->servidor->cerrarConexion();
            //eliminar datos del json
            //l->info("Sesión del" + usuario + "cerrada por ingresar contraseña incorrecta");
        } else {
            guardarUsuarioYContrasenia(usuarioNuevo, contraseniaNueva);
            //l->info("Sesión del" + usuarioNuevo + "iniciada");
        }
    } else {
        guardarUsuarioYContrasenia(usuario, contrasenia);
        //l->info("Sesión del" + usuario + "iniciada");
    }

}

bool ControladorDeSesiones::datosCorrectos(string usuario, string contrasenia){
    bool correcta = true;

    /*
     * chequear en el json. Dar 3 intentos
     */

    return correcta;
}

void ControladorDeSesiones::guardarUsuarioYContrasenia(string usuario, string contrasenia){

    /*
     * guardar en el json
     */

}