//
// Created by ailen-magali on 3/6/20.
//

#ifndef CUCURUCHO_CONTROLADORDESESIONES_H
#define CUCURUCHO_CONTROLADORDESESIONES_H

#include "ConexionServidor.h"
#include "../protocols/protocolo.h"
#include "../../server/classes/config/UsuariosConfiguracion.h"
#include <iostream>
#include <jsoncpp/json/json.h>
#include <fstream>
#include <list>
using namespace std;

class ControladorDeSesiones {
public:
    ControladorDeSesiones(ConexionServidor *conexionServidor, list<ConexionServidor *> *conexiones,
                          UsuariosConfiguracion* usuarios, int nroJugador, bool usuarioEnJuego);
    bool iniciarSesion();
    void setServidor(ConexionServidor *servidor);
    string getUsuarioConectado();

    ConexionServidor *getConexionServidor() const;

    bool controlarConUsuariosEnJuego(std::string usuario);
private:

    ConexionServidor* conexionServidor;
    UsuariosConfiguracion* usuarios;
    std::list<ConexionServidor*>* conexiones;
    int nroJugador;
    string usuarioConectado;
    bool usuarioEnJuego;

	bool usuarioEstaRegistrado(char* usuario, char* contrasenia);
	void pedirCredenciales(Login *login);
};


#endif //CUCURUCHO_CONTROLADORDESESIONES_H
