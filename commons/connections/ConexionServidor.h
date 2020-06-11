#ifndef CUCURUCHO_CONEXIONSERVIDOR_H
#define CUCURUCHO_CONEXIONSERVIDOR_H


#include <sys/socket.h>
#include "../protocols/protocolo.h"
#include "../../libraries/json/json.hpp"
#include "ConexionUtils.h"
#include "Conexion.h"


class ConexionServidor : public Conexion {
public:
	ConexionServidor(int client_socket);

	nlohmann::json recibirMensaje();
	void enviarMensaje(nlohmann::json mensaje);
	void enviarEstadoLogin(int nroJugador);
	void cerrar();

private:
	int client_socket;
};


#endif //CUCURUCHO_CONEXIONSERVIDOR_H
