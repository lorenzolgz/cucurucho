#ifndef CUCURUCHO_CONEXIONSERVIDOR_H
#define CUCURUCHO_CONEXIONSERVIDOR_H


#include <sys/socket.h>
#include "../protocols/protocolo.h"

class ConexionServidor {
public:
	ConexionServidor(int client_socket);

	struct Command recibirMensaje();
	void enviarMensaje(struct View* client_view);
	void cerrarConexion();

private:
	int client_socket;
	int receiveData(int* client_socket, struct Command* client_command);
	int sendData(int* client_socket, struct View* client_view);
};


#endif //CUCURUCHO_CONEXIONSERVIDOR_H
