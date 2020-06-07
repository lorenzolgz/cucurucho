#include "HiloConexionServidor.h"
#include "../../commons/utils/Log.h"

HiloConexionServidor::HiloConexionServidor(ConexionServidor* conexionServidor, ColaBloqueante<nlohmann::json>* colaComandos) {
	this->conexionServidor = conexionServidor;
	this->colaComandos = colaComandos;
}

void HiloConexionServidor::run() {
	while (true) {
		nlohmann::json valorRecibido = conexionServidor->recibirMensaje();
		colaComandos->push(valorRecibido);
	}
}
