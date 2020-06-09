//
// Created by ailen-magali on 3/6/20.
//

#include "ControladorDeSesiones.h"


ControladorDeSesiones::ControladorDeSesiones(ConexionServidor* conexionServidor){
    this->conexionServidor = conexionServidor;
}

bool ControladorDeSesiones::iniciarSesion(){

    //pedirle un usuario y contraseña al cliente
    struct Login logueo;
    logueo = pedirCredenciales();

    char* usuario;
    char* contrasenia;

    usuario = logueo.usuario;
    contrasenia = logueo.contrasenia;

    //verifico que el usuario esté registrado
    if(!usuarioEstaRegistrado(usuario, contrasenia)) {
        //TODO se le informa al cliente que no se le permitirá jugar
        this->conexionServidor->cerrar();
        return false;
    }

    return true;
}

bool ControladorDeSesiones::usuarioEstaRegistrado(char* usuario, char* contrasenia)
{
    bool usuarioRegistrado;
    bool contraseniaCorrecta;
    char* nuevaContrasenia;

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
        while(!contraseniaCorrecta){
            //TODO esto funciona pero para una única vez
            this->conexionServidor->enviarEstadoLogin(contraseniaCorrecta);
            nuevaContrasenia = pedirCredenciales().contrasenia;
            contraseniaCorrecta = (contrasenias[usuario] == nuevaContrasenia);
        }
    }
    this->conexionServidor->enviarEstadoLogin(contraseniaCorrecta);

    return usuarioRegistrado;
}

struct Login ControladorDeSesiones::pedirCredenciales(){
    nlohmann::json mensajeJson = this->conexionServidor->recibirMensaje();
    struct Login login;
    strcpy(login.usuario, std::string(mensajeJson["usuario"]).c_str());
    strcpy(login.contrasenia, std::string(mensajeJson["contrasenia"]).c_str());

    return login;
}

void ControladorDeSesiones::setServidor(ConexionServidor *servidor) {
    ControladorDeSesiones::conexionServidor = servidor;
}
