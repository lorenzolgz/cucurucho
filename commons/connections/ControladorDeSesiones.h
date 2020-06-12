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
    ControladorDeSesiones(ConexionServidor* conexionServidor, int nroJugador);
    bool iniciarSesion(map<string, bool> &jugadoresConectados);
    void setServidor(ConexionServidor *servidor);
    string usuarioConectado;
    string userConectado();
    bool controlarQueNoIngreseUsuarioYaEnJuego(std::string usuario, map<string, bool> &jugadoresConectados);

private:
    ConexionServidor* conexionServidor;
	Json::Value jsonUsuarios, contrasenias;
	int nroJugador;

	bool usuarioEstaRegistrado(char* usuario, char* contrasenia);
	void pedirCredenciales(Login *login);
};


#endif //CUCURUCHO_CONTROLADORDESESIONES_H
