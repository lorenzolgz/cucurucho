#include "ConexionCliente.h"
#include "../utils/Log.h"
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

ConexionCliente::ConexionCliente(int client_socket) {
	ConexionCliente::client_socket = client_socket;
}

struct EstadoTick ConexionCliente::recibirEstadoTick() {
	struct EstadoTick estadoTick;

	l->debug("Cliente por recibir mensaje");
	if (receiveDataEstadoTick(&client_socket, &estadoTick) < 0) {
		perror("Receive Data Error");
		exit(1);
	}

	l->debug("Cliente recibio estadoTick.estadoJugador.posicionX: " + std::to_string(estadoTick.estadoJugador.posicionX));

	return estadoTick;
}

struct InformacionNivel ConexionCliente::recibirInformacionNivel() {
	struct InformacionNivel informacionNivel;

	l->debug("Cliente por recibir mensaje");
	if (receiveInformacionNivel(&client_socket, &informacionNivel) < 0) {
		perror("Receive Data Error");
		exit(1);
	}

	l->debug("Cliente recibio informacionNivel: ");

	return informacionNivel;
}

void ConexionCliente::enviarMensaje(struct Comando *comando) {
	l->debug("Cliente por mandar mensaje: " + std::to_string(comando->arriba) + " " + std::to_string(comando->abajo) + " " + std::to_string(comando->izquierda)  + " " + std::to_string(comando->derecha));
	if (sendData(&client_socket, comando) < 0) {
		perror("Send Data Error");
		exit(1);
	}
	l->debug("Cliente mando mensaje");
}

void ConexionCliente::cerrarConexion() {
	close(client_socket);
}

int ConexionCliente::sendData(int* client_socket, struct Comando* client_command) {

	int total_bytes_written = 0;
	int bytes_written = 0;
	int send_data_size = sizeof(struct Comando);
	bool client_socket_still_open = true;

	while ((send_data_size > total_bytes_written) && client_socket_still_open) {
		bytes_written = send(*client_socket, (client_command + total_bytes_written),
							 (send_data_size - total_bytes_written), MSG_NOSIGNAL);

		if (bytes_written < 0) { // Error
			return bytes_written;
		} else if (bytes_written == 0) { // Socket closed
			client_socket_still_open = false;
		} else {
			total_bytes_written += bytes_written;
		}
	}

	return 0;
}

int ConexionCliente::receiveDataEstadoTick(int* client_socket, struct EstadoTick* estadoTick) {

	int total_bytes_receive = 0;
	int bytes_receive = 0;
	int receive_data_size = sizeof(struct EstadoTick); // !!!!
	bool client_socket_still_open = true;

	while ((receive_data_size > bytes_receive) && client_socket_still_open) {
		bytes_receive = recv(*client_socket, (estadoTick + total_bytes_receive),
							 (receive_data_size - total_bytes_receive), MSG_NOSIGNAL);

		if (bytes_receive < 0) { // Error
			return bytes_receive;
		} else if (bytes_receive == 0) { // Socket closed
			client_socket_still_open = false;
		} else {
			total_bytes_receive += bytes_receive;
		}
	}

	return 0;
}

int ConexionCliente::receiveInformacionNivel(int* client_socket, struct InformacionNivel* header) {

	int total_bytes_receive = 0;
	int bytes_receive = 0;
	int receive_data_size = sizeof(struct InformacionNivel); // !!!!
	bool client_socket_still_open = true;

	while ((receive_data_size > bytes_receive) && client_socket_still_open) {
		bytes_receive = recv(*client_socket, (header + total_bytes_receive),
							 (receive_data_size - total_bytes_receive), MSG_NOSIGNAL);

		if (bytes_receive < 0) { // Error
			return bytes_receive;
		} else if (bytes_receive == 0) { // Socket closed
			client_socket_still_open = false;
		} else {
			total_bytes_receive += bytes_receive;
		}
	}

	return 0;
}

