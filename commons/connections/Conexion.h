#ifndef CUCURUCHO_CONEXION_H
#define CUCURUCHO_CONEXION_H


#include <json.hpp>

class Conexion {
public:
	void enviarData2(int client_socket, nlohmann::json dataJson);
	nlohmann::json recibirData2(int client_socket);
};


#endif //CUCURUCHO_CONEXION_H
