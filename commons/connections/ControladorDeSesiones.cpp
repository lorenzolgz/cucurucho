//
// Created by ailen-magali on 3/6/20.
//

#include "ControladorDeSesiones.h"


ControladorDeSesiones::ControladorDeSesiones(ConexionServidor* conexionServidor){
    this->servidor = conexionServidor;
}

void ControladorDeSesiones::iniciarSesion(){

    //TODO pedirle un usuario y contraseña al cliente
    string usuario = "ailu";
    string contrasenia = "5678";

    //verifico que el usuario esté registrado
    if(!usuarioEstaRegistrado(usuario, contrasenia)) {
        //TODO se le informa al cliente que no se le permitirá jugar
        this->servidor->cerrarConexion();
    }
}

bool ControladorDeSesiones::usuarioEstaRegistrado(string usuario, string contrasenia)
{
    bool usuarioRegistrado;
    bool contraseniaCorrecta;

    //abro json de usuarios
    Json::Value jsonUsuarios, usuarios;
    ifstream archivo(JSON_USUARIOS, ifstream::binary);
    archivo >> jsonUsuarios;
    usuarios = jsonUsuarios["usuariosRegistrados"];

    //chequeo si el usuario está registrado
    usuarioRegistrado = !(usuarios[usuario].asString().empty());

    //si está registrado, verifico la contraseña
    if(usuarioRegistrado){
        contraseniaCorrecta = (usuarios[usuario].asString() == contrasenia);
        if(!contraseniaCorrecta){
            //TODO pedirle al cliente que vuelva a ingresarla o anular la conexion (ver)
        }
    }

    return usuarioRegistrado;
}

