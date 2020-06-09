#ifndef CUCURUCHO_HILOCONEXIONSERVIDOR_H
#define CUCURUCHO_HILOCONEXIONSERVIDOR_H


#include <jsoncpp/json/json.h>
#include "../../commons/Thread.h"
#include "../../commons/connections/ConexionServidor.h"
#include "../../commons/ColaBloqueante.h"

class HiloConexionServidor : public Thread {
public:
	HiloConexionServidor(ConexionServidor* conexionServidor);
	void run() override;
	void enviarEstadoTick(struct EstadoTick* estadoTick);
	void enviarInformacionNivel(struct InformacionNivel* header);
	ConexionServidor* conexionServidor;
	ColaBloqueante<nlohmann::json>* colaReceptora = new ColaBloqueante<nlohmann::json>();
	ColaBloqueante<nlohmann::json>* colaEnviadora = new ColaBloqueante<nlohmann::json>();
};


#endif //CUCURUCHO_HILOCONEXIONSERVIDOR_Hinicial que
