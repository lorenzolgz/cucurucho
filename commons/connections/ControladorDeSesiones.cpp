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

    char* usuario = login.usuario;
    char* contrasenia = login.contrasenia;

    //verifico que el usuario esté registrado
    if(!usuarioEstaRegistrado(usuario, contrasenia)){
        //TODO se le informa al cliente que no se le permitirá jugar
        this->servidor->cerrar();
        ok = false;
    }

    //se verifica que ese usuario REGISTRADO no esté en juego ya
    map<string, bool>::iterator i = this->jugadoresConectados.find(usuario);

    if(i != this->jugadoresConectados.end()){ //si existe ese usuario en el map
        if(this->jugadoresConectados[usuario]) {//si ese usuario está jugando
            //TODO informar que ya se encuentra en juego alguien con ese nombre de usuario
            cout << "Ya se encuentra en juego alguien con ese nombre de usuario" << endl;
            ok = false;
        } else { //TODO si ese usuario se conectó en esta partida pero se fue, ponerle false
            cout<<"Te desconectaste y volviste"<<endl;
            this->jugadoresConectados[usuario] = true; //ver reconexión
        }
        //usuario que no posee un bool
        cout<<"Es basura"<<endl;
        this->jugadoresConectados.erase(usuario); //lo elimino del map
        ok = false;

    } else { //si no se conectó en esta partida alguien con ese nombre de usuario
        cout<<"No se encuentra en juego todavía alguien con ese nombre de usuario"<<endl;
        this->jugadoresConectados.insert({usuario, true});
    }

    cout<<"Usuario "<<usuario<<" entró al juego"<<endl;

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

map<string, bool> ControladorDeSesiones::getJugadoresConectados(){
    return this->jugadoresConectados;
}

