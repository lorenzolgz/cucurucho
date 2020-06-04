//
// Created by ailen-magali on 3/6/20.
//

#ifndef CUCURUCHO_CONTROLADORDESESIONES_H
#define CUCURUCHO_CONTROLADORDESESIONES_H

#define JSON_USUARIOS "../server/usuarios.json"
#include "ConexionServidor.h"
#include <iostream>
#include <jsoncpp/json/json.h>
#include <fstream>
using namespace std;

class ControladorDeSesiones {
public:
    ControladorDeSesiones(ConexionServidor* conexionServidor);
    void iniciarSesion();

private:
    ConexionServidor* servidor;
    bool usuarioEstaRegistrado(string usuario, string contrasenia);
};


#endif //CUCURUCHO_CONTROLADORDESESIONES_H
