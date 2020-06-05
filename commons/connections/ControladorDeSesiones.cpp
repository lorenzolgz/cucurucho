//
// Created by ailen-magali on 3/6/20.
//

#include "ControladorDeSesiones.h"


ControladorDeSesiones::ControladorDeSesiones(ConexionServidor* conexionServidor){
    this->servidor = conexionServidor;
}

void ControladorDeSesiones::iniciarSesion(){

    //pedirle un usuario y contraseña al cliente
    struct Logueo logueo;
    logueo = pedir();

    char* usuario;
    char* contrasenia;

    usuario = logueo.usuario;
    contrasenia = logueo.contrasenia;

    //verifico que el usuario esté registrado
    if(!usuarioEstaRegistrado(usuario, contrasenia)) {
        //TODO se le informa al cliente que no se le permitirá jugar
        servidor->cerrarConexion();
    }
}

bool ControladorDeSesiones::usuarioEstaRegistrado(char* usuario, char* contrasenia)
{
    bool usuarioRegistrado;
    bool contraseniaCorrecta;

    //abro json de usuarios
    Json::Value jsonUsuarios, contrasenias;
    ifstream archivo(JSON_USUARIOS, ifstream::binary);
    archivo >> jsonUsuarios;
    contrasenias = jsonUsuarios["usuariosRegistrados"];

    //chequeo si el usuario está registrado
    usuarioRegistrado = !(contrasenias[usuario].empty());


    //si está registrado, verifico la contraseña
    if(usuarioRegistrado){
        contraseniaCorrecta = (contrasenias[usuario] == contrasenia);
        if(!contraseniaCorrecta){
            //TODO pedirle al cliente que vuelva a ingresarla o anular la conexion (ver)
            servidor->cerrarConexion();
        }
    }

    return usuarioRegistrado;
}

struct Logueo ControladorDeSesiones::pedir(){
    return servidor->recibirDatosDeLogueo();
}

