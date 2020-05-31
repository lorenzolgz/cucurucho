//
// Created by rodrigosouto on 30/5/20.
//

#ifndef CUCURUCHO_CONEXIONCLIENTE_H
#define CUCURUCHO_CONEXIONCLIENTE_H


#include <sys/socket.h>
#include "../protocols/protocolo.h"

class ConexionCliente {
public:
	ConexionCliente(int client_socket);

	struct View recibirMensaje();
	void enviarMensaje(struct Command* client_command);
	void cerrarConexion();

private:
	int client_socket;
	int receiveData(int* client_socket, struct View* client_view);
	int sendData(int* client_socket, struct Command* client_command);
};


#endif //CUCURUCHO_CONEXIONCLIENTE_H
