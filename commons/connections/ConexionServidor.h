#ifndef CUCURUCHO_CONEXIONSERVIDOR_H
#define CUCURUCHO_CONEXIONSERVIDOR_H


#include <sys/socket.h>
#include "../protocols/protocolo.h"
#include <json.hpp>
#include "ConexionUtils.h"
#include "Conexion.h"


class ConexionServidor : public Conexion {
public:
	ConexionServidor(int client_socket);

	nlohmann::json recibirMensaje();
	void enviarEstadoTick(struct EstadoTick* estadoTick);
	void enviarInformacionNivel(struct InformacionNivel* header);
	void cerrar();

private:
	int client_socket;
};


#endif //CUCURUCHO_CONEXIONSERVIDOR_H
