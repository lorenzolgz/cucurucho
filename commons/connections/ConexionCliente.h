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

	struct EstadoTick recibirEstadoTick();

	struct InformacionNivel recibirInformacionNivel();

	void enviarComando(struct Comando* comando);

	void cerrar();

private:
	int server_socket;
};


#endif //CUCURUCHO_CONEXIONCLIENTE_H
