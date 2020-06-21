#ifndef CUCURUCHO_CONEXIONCLIENTE_H
#define CUCURUCHO_CONEXIONCLIENTE_H


#include <sys/socket.h>
#include <jsoncpp/json/json.h>
#include "../protocols/protocolo.h"
#include "ConexionUtils.h"
#include "Conexion.h"
#include "../../commons/ColaBloqueante.h"


class ConexionCliente : public Conexion {
public:
	ConexionCliente(int server_socket);

    nlohmann::json recibirMensaje();

	void enviarComando(struct Comando* comando);

    void enviarDatosDeLogin(Login *logueo);

    void cerrar();

private:
	int server_socket;

};


#endif //CUCURUCHO_CONEXIONCLIENTE_H
