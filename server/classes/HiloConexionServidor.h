#ifndef CUCURUCHO_HILOCONEXIONSERVIDOR_H
#define CUCURUCHO_HILOCONEXIONSERVIDOR_H


#include <jsoncpp/json/json.h>
#include "../../commons/Thread.h"
#include "../../commons/connections/ConexionServidor.h"
#include "../../commons/ColaBloqueante.h"

class HiloConexionServidor : public Thread {
public:
	HiloConexionServidor(ConexionServidor* conexionServidor, ColaBloqueante<nlohmann::json>* colaComandos);
	void run() override;

private:
	ConexionServidor* conexionServidor;
	ColaBloqueante<nlohmann::json>* colaComandos;
};


#endif //CUCURUCHO_HILOCONEXIONSERVIDOR_Hinicial que
