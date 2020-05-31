#ifndef CUCURUCHO_CONEXIONCLIENTE_H
#define CUCURUCHO_CONEXIONCLIENTE_H


#include <sys/socket.h>
#include "../protocols/protocolo.h"

class ConexionCliente {
public:
	ConexionCliente(int client_socket);

	struct EstadoTick recibirEstadoTick();
	struct InformacionNivel recibirInformacionNivel();
	void enviarMensaje(struct Comando* comando);
	void cerrarConexion();

private:
	int client_socket;
	int receiveDataEstadoTick(int* client_socket, struct EstadoTick* estadoTick);
	int receiveInformacionNivel(int* client_socket, struct InformacionNivel* header);
	int sendData(int* client_socket, struct Comando* client_command);
};


#endif //CUCURUCHO_CONEXIONCLIENTE_H
