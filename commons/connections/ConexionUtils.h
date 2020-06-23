#ifndef CUCURUCHO_CONEXIONUTILS_H
#define CUCURUCHO_CONEXIONUTILS_H

#include <sys/socket.h>
#include "../utils/Log.h"

template <class T>
int recibirData(int *client_socket, T *data) {
	int total_bytes_receive = 0;
	int bytes_receive = 0;
	int receive_data_size = sizeof(T);
	bool client_socket_still_open = true;

	// Receive
	// ssize_t recv(int sockfd, void *buf, size_t len, int flags);
	// sockfd -> file descriptor that refers to estadosEnemigos socket
	// buf -> where the received message into the buffer buf.
	// len -> The caller must specify the size of the buffer in len.
	// flags
	// The recv() call are used to receive messages from estadosEnemigos socket.
	// If no messages are available at the socket, the receive call wait for estadosEnemigos message to arrive. (Blocking)

	while ((receive_data_size > bytes_receive) && client_socket_still_open) {
		bytes_receive = recv(*client_socket, (data + total_bytes_receive),
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

template <class T>
int _recibirData(int *client_socket, T *data, int bytesTotalesARecibir) {
	int total_bytes_receive = 0;
	int bytes_receive = 0;
	bool client_socket_still_open = true;

	// Receive
	// ssize_t recv(int sockfd, void *buf, size_t len, int flags);
	// sockfd -> file descriptor that refers to estadosEnemigos socket
	// buf -> where the received message into the buffer buf.
	// len -> The caller must specify the size of the buffer in len.
	// flags
	// The recv() call are used to receive messages from estadosEnemigos socket.
	// If no messages are available at the socket, the receive call wait for estadosEnemigos message to arrive. (Blocking)

	while ((bytesTotalesARecibir > bytes_receive) && client_socket_still_open) {
		bytes_receive = recv(*client_socket, (data + total_bytes_receive),
							 (bytesTotalesARecibir - total_bytes_receive), MSG_NOSIGNAL);
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

template <class T>
int enviarData(int* client_socket, T* data) {

	int total_bytes_written = 0;
	int bytes_written = 0;
	int send_data_size = sizeof(T);
	bool client_socket_still_open = true;

	while ((send_data_size > total_bytes_written) && client_socket_still_open) {
		bytes_written = send(*client_socket, (data + total_bytes_written),
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

template <class T>
int _enviarData(int* client_socket, T* data, int bytesTotalesAEnviar) {

	int total_bytes_written = 0;
	int bytes_written = 0;
	bool client_socket_still_open = true;

	while ((bytesTotalesAEnviar > total_bytes_written) && client_socket_still_open) {
		bytes_written = send(*client_socket, (data + total_bytes_written),
							 (bytesTotalesAEnviar - total_bytes_written), MSG_NOSIGNAL);

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

#endif //CUCURUCHO_CONEXIONUTILS_H
