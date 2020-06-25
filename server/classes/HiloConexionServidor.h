#ifndef CUCURUCHO_HILOCONEXIONSERVIDOR_H
#define CUCURUCHO_HILOCONEXIONSERVIDOR_H


#include <jsoncpp/json/json.h>
#include "../../commons/Thread.h"
#include "../../commons/connections/ConexionServidor.h"
#include "../../commons/ColaBloqueante.h"
#include "../../commons/connections/AceptadorConexiones.h"

class HiloConexionServidor : public Thread {
public:
	int jugador;
	bool activo;
	std::string username;
	ConexionServidor* conexionServidor;

	HiloConexionServidor(ConexionServidor* conexionServidor, int jugador, std::string username);

	void run() override;
	void enviarEstadoTick(struct EstadoTick* estadoTick);
	void enviarInformacionNivel(struct InformacionNivel* header);
	void terminar();
	ColaBloqueante<nlohmann::json>* colaReceptora = new ColaBloqueante<nlohmann::json>();
	ColaBloqueante<nlohmann::json>* colaEnviadora = new ColaBloqueante<nlohmann::json>();

private:
	InformacionNivel *informacionNivelActual;
	bool continuarLoopeando;

	void cicloReconectar();
};


#endif //CUCURUCHO_HILOCONEXIONSERVIDOR_Hinicial que
