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

const struct Login autoCredenciales[4] = {{"rodri", "13141516"},
        {"cami", "1234"},
        {"ailu", "5678"},
        {"lolo", "9012"}};

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

    void tick(std::string input, int estado, bool *validarLogin);

    bool estaActivada(bool enter, int estadoLogin);

    void getCredenciales(struct Login* login);

private:
    TituloVista* tituloVista;
    int contador;
    int inicioTimeout;
    bool activada;
    std::string username;
    std::string password;
    bool seleccionadoUsuario;
    int estado;
    bool autoCompletar;
    int autoCompletarIndice;

    void leerInput(std::string input, bool *validarLogin);
};

#endif //CUCURUCHO_TITULO_H
