//
// Created by rodrigosouto on 30/5/20.
//

#include "ConexionCliente.h"
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>

ConexionCliente::ConexionCliente(int client_socket) {
	ConexionCliente::client_socket = client_socket;
}

struct View ConexionCliente::recibirMensaje() {
	struct View client_view;

	if (receiveData(&client_socket, &client_view) < 0) {
		perror("Receive Data Error");
		// !!!! status = -1;
		exit(1);
	}

	return client_view;
}

void ConexionCliente::enviarMensaje(struct Command *client_command) {
	if (sendData(&client_socket, client_command) < 0) {
		perror("Send Data Error");
		exit(1);
	}
}

void ConexionCliente::cerrarConexion() {
	close(client_socket);
}

int ConexionCliente::sendData(int* client_socket, struct Command* client_command) {

	int total_bytes_written = 0;
	int bytes_written = 0;
	int send_data_size = sizeof(struct Command);
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

int ConexionCliente::receiveData(int* client_socket, struct View* client_view) {

	int total_bytes_receive = 0;
	int bytes_receive = 0;
	int receive_data_size = sizeof(struct View);
	bool client_socket_still_open = true;

	while ((receive_data_size > bytes_receive) && client_socket_still_open) {
		bytes_receive = recv(*client_socket, (client_view + total_bytes_receive),
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
