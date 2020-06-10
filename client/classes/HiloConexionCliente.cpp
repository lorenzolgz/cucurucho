//
// Created by camix on 9/6/20.
//

#include "HiloConexionCliente.h"

HiloConexionCliente::HiloConexionCliente(ConexionCliente *conexionCliente,
                                         ColaBloqueante<nlohmann::json> *colaComandos) {
    HiloConexionCliente::conexionCliente = conexionCliente;
    HiloConexionCliente::colaComandos = colaComandos;

}


void HiloConexionCliente::run() {
	l->info("Comenzando a correr HiloConexionCliente");

	while (true) {
		l->error("!!!! whileHiloConexionServidor");
		nlohmann::json mensajeRecibido = conexionCliente->recibirMensaje();
		l->error("!!!! HiloConexionCliente " + mensajeRecibido.dump());
		colaComandos->push(mensajeRecibido);
    }
}
