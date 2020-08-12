//
// Created by javier on 10/5/20.
//

#ifndef CUCURUCHO_TITULO_H
#define CUCURUCHO_TITULO_H

#include "../view/TituloVista.h"
#include "../../../commons/protocols/protocolo.h"
#include "../../../commons/connections/ConexionCliente.h"
#include "../Audio.h"
#include <string>

const struct Login autoCredenciales[5] = {{"rodri", "12"},
        {"cami", "12"},
        {"ailu", "12"},
        {"lolo", "12"},
        {"javi", "12"}};

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
    Titulo(int ancho, int alto, bool conexionPerdida);

    void tick(std::string input, int estado, bool *validarLogin);

    void estaActivada(bool enter);

    void getCredenciales(struct Login* login);

    void setAutoCompletar();

    void reiniciarPassword();

private:
    TituloVista* tituloVista;
    int contador;
    int timeoutAuto;
    bool activada;
    std::string username;
    std::string password;
    bool seleccionadoUsuario;
    int estado;
    bool autoCompletar;
    int autoCompletarIndice;

    void leerInput(std::string input, bool *validarLogin);

    Audio* audio;
    std::string audioErrorUsuario;
	std::string audioInicioPartida;
	std::string audioInput;
};

#endif //CUCURUCHO_TITULO_H
