//
// Created by ailen-magali on 3/6/20.
//

#ifndef CUCURUCHO_CONTROLADORDESESIONES_H
#define CUCURUCHO_CONTROLADORDESESIONES_H

#define JSON_USUARIOS "../server/usuarios.json"
#include "ConexionServidor.h"
#include "../protocols/protocolo.h"
#include <iostream>
#include <jsoncpp/json/json.h>
#include <fstream>
using namespace std;

class ControladorDeSesiones {
public:
    ControladorDeSesiones(ConexionServidor* conexionServidor);
    bool iniciarSesion();
    map<string, bool> getJugadoresConectados();
    void setServidor(ConexionServidor *servidor);

private:
    ConexionServidor* servidor;
    bool usuarioEstaRegistrado(char* usuario, char* contrasenia);
    struct Login pedirCredenciales();
    map<string, bool> jugadoresConectados;
    Json::Value jsonUsuarios, contrasenias;
};


#endif //CUCURUCHO_CONTROLADORDESESIONES_H
