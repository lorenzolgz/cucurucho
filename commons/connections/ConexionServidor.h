#ifndef CUCURUCHO_CONEXIONSERVIDOR_H
#define CUCURUCHO_CONEXIONSERVIDOR_H


#include <sys/socket.h>
#include "../protocols/protocolo.h"

class ConexionServidor {
public:
	ConexionServidor(int client_socket);

	struct Comando recibirMensaje();
	void enviarMensaje(struct EstadoTick* estadoTick);
	void cerrarConexion();

private:
	int client_socket;
	int receiveData(int* client_socket, struct Comando* client_command);
	int sendData(int* client_socket, struct EstadoTick* estadoTick);
};


#endif //CUCURUCHO_CONEXIONSERVIDOR_H
