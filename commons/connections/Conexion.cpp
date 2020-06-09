#include "Conexion.h"
#include "ConexionUtils.h"

void Conexion::enviarData2(int client_socket, nlohmann::json dataJson) {


    std::string mensajeStr = dataJson.dump();
	uint32_t tamanioMensaje = mensajeStr.size();


    if (_enviarData(&client_socket, &tamanioMensaje, sizeof(tamanioMensaje)) < 0) {
		perror("Send Data Error 1");
		exit(1);
	}
	if (_enviarData(&client_socket, &mensajeStr[0], tamanioMensaje) < 0) {
		perror("Send Data Error 2");
		exit(1);
	}
}

nlohmann::json Conexion::recibirData2(int client_socket) {
	uint32_t tamanioMensaje;

	if (_recibirData<uint32_t>(&client_socket, &tamanioMensaje, sizeof(uint32_t)) < 0) {
		perror("recibirMensaje. Error cuando se recibe tamanioMensaje");
		exit(1);
	}

	std::string mensajeStr(tamanioMensaje, '\0');
	if (_recibirData<char>(&client_socket, &mensajeStr[0], tamanioMensaje) < 0) {
	    perror("recibirMensaje. Error cuando se recibe mensaje json");
		exit(1);
	}

	nlohmann::json mensajeJson = nlohmann::json::parse(mensajeStr);
    return mensajeJson;
}
