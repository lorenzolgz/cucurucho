#include "IniciadorComunicacion.h"
#include "ConexionCliente.h"
#include "../utils/Log.h"

IniciadorComunicacion::IniciadorComunicacion(char* ip_address, int port) {
	IniciadorComunicacion::ip_address = ip_address;
	IniciadorComunicacion::port = port;
}

ConexionCliente* IniciadorComunicacion::conectar() {
	int client_socket;
	struct sockaddr_in server;

	l->info("Arguments: 1) ip: " + (std::string) ip_address + "%s ,2) port: " + std::to_string(port));

	// Create Socket
	// int socket(int domain, int type, int protocol);
	// Domain: AF_INET (IPv4 Internet protocols)
	// Type: SOCK_STREAM (Provides  sequenced,  reliable, two-way connection-based byte streams.)
	// Protocol: 0 (chosen automatically)
	client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == -1) {
		perror("Could not create socket");
		exit(1);
	}
	l->info("Socket created");
	//------------------------

	// Prepare the sockaddr_in structure
	server.sin_addr.s_addr = inet_addr((const char *) ip_address);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	//------------------------

	//Connect to remote server
	// int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	// sockfd -> file descriptor that refers to estadosEnemigos socket
	// addr -> pointer to sockaddr_in structure for the SERVER.
	// addrlen -> size of sockaddr_in structure for the SERVER.
	// The connect() system call connects the socket referred to by the file descriptor sockfd to the address specified by addr.
	if (connect(client_socket, (struct sockaddr *) &server, sizeof(struct sockaddr_in)) < 0) {
		perror("connect failed. Error");
		exit(1);
	}

	l->info("Connected");

	return new ConexionCliente(client_socket);
}
