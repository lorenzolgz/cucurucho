//
// Created by rodrigosouto on 30/5/20.
//

#include "AceptadorConexiones.h"

AceptadorConexiones::AceptadorConexiones(int port) {
	AceptadorConexiones::port = port;
}

void AceptadorConexiones::escuchar() {
	struct sockaddr_in server_addr;

	// Create Socket
	// int socket(int domain, int type, int protocol);
	// Domain: AF_INET (IPv4 Internet protocols)
	// Type: SOCK_STREAM (Provides  sequenced,  reliable, two-way connection-based byte streams.)
	// Protocol: 0 (chosen automatically)
	server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (server_socket == -1) {
		perror("Could not create socket");
		exit(1);
	}
	//------------------------

	// Prepare the sockaddr_in structure
	/* Structures for handling internet addresses
	struct sockaddr_in {
		short            sin_family;   // e.g. AF_INET
		unsigned short   sin_port;     // e.g. htons(3490)
		struct in_addr   sin_addr;     // see struct in_addr, below
		char             sin_zero[8];  // zero this if you want to
	};
	struct in_addr {
		unsigned long s_addr;  // load with inet_aton()
	}; */
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY; //Address to accept any incoming messages. INADDR_ANY accepts any.
	server_addr.sin_port = htons(port); // The htons() function converts the unsigned short integer hostshort from host byte order to network byte order.
	//------------------------

	// Bind
	// int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	// sockfd -> file descriptor that refers to a socket
	// addr -> pointer to sockaddr_in structure of the SERVER
	// addrlen -> size of the sockaddr_in structure
	// bind() assigns the address specified by addr to the socket referred to by the file descriptor sockfd.
	if (bind(server_socket, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0) {
		perror("Bind failed. Error");
		exit(1);
	}
	printf("Bind done\n");
	//------------------------

	// Listen
	// int listen(int sockfd, int backlog);
	// sockfd -> file descriptor that refers to a socket,in this case of type SOCK_STREAM
	// backlog-> The backlog argument defines the maximum length to which the queue of pending connections for sockfd may grow.
	// listen() marks the socket referred to by sockfd as a passive socket, that is, as a socket that will be used to accept incoming connection requests using accept();
	if (listen(server_socket, 3) < 0) {
		perror("Listen failed. Error");
		exit(1);
	}
	printf("Listening on port: %d Waiting for incoming connections...\n", port);
	//------------------------
}

ConexionServidor *AceptadorConexiones::aceptarConexion() {
	struct sockaddr_in client_addr;
	int client_addrlen;

	// Accept incoming connection from a client
	// int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
	// sockfd -> socket that has been created with socket(), bound to a local address with bind(), and is listening for connections after a listen()
	// addr -> pointer to a sockaddr structure for the CLIENT.
	// addrlen -> size of sockaddr structure for the CLIENT.
	printf("%d\n\n\n", server_socket);
	int client_socket = accept(server_socket, (struct sockaddr *) &client_addr, (socklen_t *) &client_addrlen);
	if (client_socket < 0) {
		perror("Accept failed");
		exit(1);
	}

	return new ConexionServidor(client_socket);
}

void AceptadorConexiones::dejarDeEscuchar() {
	close(server_socket);
}
