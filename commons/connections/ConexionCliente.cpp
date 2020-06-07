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

int ConexionCliente::sincronizarInicio(){

    int bytes_written = -1;
    int bytes_receive = -1;
    bool inicio = false;
    bool validado = true;
    int retry = 0;

    while((bytes_receive < 0 || !inicio) && retry < 1000){
        std::cout << "VALIDANDO INICIO";
        bytes_receive = recv(client_socket, &inicio, sizeof(inicio), MSG_NOSIGNAL);
        retry++;
    }
    while(bytes_written < 0 && retry < 1000){
        std::cout << "ENVIANDO INICIO";
        bytes_written = send(client_socket, &validado, sizeof(inicio), MSG_NOSIGNAL);
        retry++;
    }

    if(retry < 100){
        return 1;
    }

    return -1;

}

struct EstadoTick ConexionCliente::recibirEstadoTick() {
	struct EstadoTick estadoTick;

	l->debug("Cliente por recibir mensaje");
	if (receiveDataEstadoTick(&client_socket, &estadoTick) < 0) {
		perror("Receive Data Error");
		// exit(1);
	}

	l->debug("Cliente recibio estadoTick.estadoJugador.posicionX: " + std::to_string(estadoTick.estadosJugadores[0].posicionX));

	return estadoTick;
}

struct InformacionNivel ConexionCliente::recibirInformacionNivel() {
	struct InformacionNivel informacionNivel;

	l->debug("Cliente por recibir mensaje");
	if (receiveInformacionNivel(&client_socket, &informacionNivel) < 0) {
		perror("Receive Data Error");
		// exit(1);
	}

	l->debug("Cliente recibio informacionNivel: ");

	return informacionNivel;
}

void ConexionCliente::enviarMensaje(struct Comando *comando) {
	l->debug("Cliente por mandar mensaje: " + std::to_string(comando->arriba) + " " + std::to_string(comando->abajo) + " " + std::to_string(comando->izquierda)  + " " + std::to_string(comando->derecha));
	if (sendData(&client_socket, comando) < 0) {
		perror("Send Data Error enviarMensaje");
		exit(1);
	}
	l->debug("Cliente mando mensaje");
}

//---------------------------para login------------------------

void ConexionCliente::enviarDatosDeLogin(struct Login *logueo){
    //que lo loguee
    if(enviarUsuarioYContrasenia(&client_socket, logueo) < 0){
        perror("Send Data Error enviarDatosDeLogin");
        // exit(1);
    }
    l->debug("Cliente mando datos de logueo");
}

int ConexionCliente::enviarUsuarioYContrasenia(int* client_socket, struct Login* logueo){
    int total_bytes_written = 0;
    int bytes_written = 0;
    int send_data_size = sizeof(struct Login);
    bool client_socket_still_open = true;

    while ((send_data_size > total_bytes_written) && client_socket_still_open) {
        bytes_written = send(*client_socket, (logueo + total_bytes_written),
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

bool ConexionCliente::contraseniaCorrecta(){
    bool esCorrecta = false;

    l->debug("Cliente por recibir mensaje");
    if (recibirValidacionContrasenia(&client_socket, &esCorrecta) < 0) {
        perror("Receive Data Error");
        //exit(1);
    }
    return esCorrecta;
}

int ConexionCliente::recibirValidacionContrasenia(int* client_socket, bool* esCorrecta){
    int total_bytes_receive = 0;
    int bytes_receive = 0;
    int receive_data_size = sizeof(bool); // !!!!
    bool client_socket_still_open = true;

    while ((receive_data_size > bytes_receive) && client_socket_still_open) {
        bytes_receive = recv(*client_socket, (esCorrecta + total_bytes_receive),
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

//----------------------------------fin logueo---------------------------------------

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

