//
// Created by ailen-magali on 3/6/20.
//

#ifndef CUCURUCHO_CONTROLADORDESESIONES_H
#define CUCURUCHO_CONTROLADORDESESIONES_H

#include "ConexionServidor.h"
#include <iostream>
using namespace std;

class ControladorDeSesiones {
public:
    ControladorDeSesiones(ConexionServidor* conexionServidor);
    void iniciarSesion();

private:
    ConexionServidor* servidor;
    bool datosCorrectos(string usuario, string contrasenia);
    void guardarUsuarioYContrasenia(string usuario, string contrasenia);
};


#endif //CUCURUCHO_CONTROLADORDESESIONES_H
