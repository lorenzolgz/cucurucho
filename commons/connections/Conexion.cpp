#include "Conexion.h"
#include "ConexionUtils.h"
#include "ConexionExcepcion.h"

void Conexion::enviarData2(int client_socket, nlohmann::json dataJson) {
    std::string mensajeStr = dataJson.dump();
    uint32_t tamanioMensaje = mensajeStr.size();

    if (_enviarData(&client_socket, &tamanioMensaje, sizeof(tamanioMensaje)) <= 0) {
        l->error("Error al enviar size del mensaje: " + (errno != 0 ? std::string(strerror(errno)) : ""));
        throw ConexionExcepcion();
    }
    if (_enviarData(&client_socket, &mensajeStr[0], tamanioMensaje) <= 0) {
        l->error("Error al enviar mensaje JSON: " + (errno != 0 ? std::string(strerror(errno)) : ""));
        throw ConexionExcepcion();
    }
}

nlohmann::json Conexion::recibirData2(int client_socket) {
    uint32_t tamanioMensaje;

    if (_recibirData<uint32_t>(&client_socket, &tamanioMensaje, sizeof(uint32_t)) <= 0) {
        l->error("Error al recibir size del mensaje: " + (errno != 0 ? std::string(strerror(errno)) : ""));
        throw ConexionExcepcion();
    }
    l->debug("conexionTamanio: " + std::to_string(tamanioMensaje));

    std::string mensajeStr(tamanioMensaje, '\0');
    if (_recibirData<char>(&client_socket, &mensajeStr[0], tamanioMensaje) <= 0) {
        l->error("Error al recibir mensaje JSON: " + (errno != 0 ? std::string(strerror(errno)) : ""));
        throw ConexionExcepcion();
    }

    l->debug("Conexion recibio:  " + mensajeStr);
	nlohmann::json mensajeJson;

    if (mensajeStr.empty()) {
        l->error("Conexion recibio un mensaje vacio");
        return mensajeJson;
        throw ConexionExcepcion();
    }

    mensajeJson = nlohmann::json::parse(mensajeStr);
    return mensajeJson;
}