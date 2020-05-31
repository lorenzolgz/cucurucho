#ifndef CUCURUCHO_ACEPTADORCONEXIONES_H
#define CUCURUCHO_ACEPTADORCONEXIONES_H


#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include "ConexionServidor.h"


class AceptadorConexiones {
public:
	AceptadorConexiones(int port);

	void escuchar();
	ConexionServidor* aceptarConexion();
	void dejarDeEscuchar();

private:
	int port;
	int server_socket;
};


#endif //CUCURUCHO_ACEPTADORCONEXIONES_H
