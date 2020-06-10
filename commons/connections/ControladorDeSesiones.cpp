//
// Created by ailen-magali on 3/6/20.
//

#include "ControladorDeSesiones.h"


ControladorDeSesiones::ControladorDeSesiones(ConexionServidor* conexionServidor){
    this->servidor = conexionServidor;
    ifstream archivo(JSON_USUARIOS, ifstream::binary);
    archivo >> this->jsonUsuarios;
    this->contrasenias = jsonUsuarios["usuariosRegistrados"];
}

bool ControladorDeSesiones::iniciarSesion(){

    bool ok = true;

    //pedirle un usuario y contraseña al cliente
    struct Login login;
    login = pedirCredenciales();

    char* usuario;
    usuario = login.usuario;
    char* contrasenia;
    contrasenia = login.contrasenia;

    //verifico que el usuario esté registrado
    if(!usuarioEstaRegistrado(usuario, contrasenia)){
        //TODO se le informa al cliente que no se le permitirá jugar
        this->servidor->cerrar();
        ok = false;
    } else {
        this->usuarioConectado = (string)usuario;
    }

    return ok;
}

bool ControladorDeSesiones::usuarioEstaRegistrado(char* usuario, char* contrasenia)
{
    bool usuarioRegistrado;
    bool contraseniaCorrecta;
    char* nuevaContrasenia;

    //chequeo si el usuario está registrado
    usuarioRegistrado = !(this->contrasenias[usuario].empty());

    //si está registrado, verifico la contraseña
    if(usuarioRegistrado){
        contraseniaCorrecta = (this->contrasenias[usuario] == contrasenia);
        while(!contraseniaCorrecta){
            this->servidor->enviarEstadoLogin(contraseniaCorrecta);
            nuevaContrasenia = pedirCredenciales().contrasenia;
            contraseniaCorrecta = (this->contrasenias[usuario] == nuevaContrasenia);
        }
    }
    this->servidor->enviarEstadoLogin(contraseniaCorrecta);

    return usuarioRegistrado;
}

struct Login ControladorDeSesiones::pedirCredenciales(){
    nlohmann::json mensajeJson = this->servidor->recibirMensaje();
    struct Login login;
    strcpy(login.usuario, std::string(mensajeJson["usuario"]).c_str());
    strcpy(login.contrasenia, std::string(mensajeJson["contrasenia"]).c_str());

    return login;
}

void ControladorDeSesiones::setServidor(ConexionServidor *servidor) {
    this->servidor = servidor;
}

string ControladorDeSesiones::userConectado(){
    return this->usuarioConectado;
}

