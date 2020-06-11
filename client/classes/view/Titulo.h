//
// Created by javier on 10/5/20.
//

#ifndef CUCURUCHO_TITULO_H
#define CUCURUCHO_TITULO_H

#include "../view/TituloVista.h"
#include "../../../commons/protocols/protocolo.h"
#include "../../../commons/connections/ConexionCliente.h"
#include <string>

const int INICIO_TIMEOUT = 120;

enum {
    TITULO_VACIO,
    TITULO_INGRESAR,
    TITULO_VALIDAR,
    TITULO_ERROR_AUTENTICACION,
    TITULO_ERROR_CONEXION,
    TITULO_ACEPTADO
};

class Titulo {
public:
    Titulo(int ancho, int alto);

    int tick(std::string input, ConexionCliente *pCliente);

    bool estaActivada(bool enter);

private:
    TituloVista* tituloVista;
    int contador;
    int inicioTimeout;
    bool activada;
    std::string username;
    std::string password;
    bool seleccionadoUsuario;
    int estado;

    void leerInput(std::string input);

    int validarLogin(ConexionCliente *pCliente);
};

#endif //CUCURUCHO_TITULO_H
