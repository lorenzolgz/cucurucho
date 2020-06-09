#ifndef CUCURUCHO_CONEXIONCLIENTE_H
#define CUCURUCHO_CONEXIONCLIENTE_H


#include <sys/socket.h>
#include <jsoncpp/json/json.h>
#include "../protocols/protocolo.h"
#include "ConexionUtils.h"
#include "Conexion.h"


class ConexionCliente : public Conexion {
public:
	ConexionCliente(int client_socket);

    void recibirMensaje(InformacionNivel *informacionNivel, EstadoTick *estadoTick);

	struct EstadoTick recibirEstadoTick();

	struct InformacionNivel recibirInformacionNivel();

	void enviarComando(struct Comando* comando);

    bool contraseniaCorrecta();

    void enviarDatosDeLogin(Login *logueo);

	void cerrar();

private:
	int server_socket;
    nlohmann::json mensaje;

};


#endif //CUCURUCHO_CONEXIONCLIENTE_H
