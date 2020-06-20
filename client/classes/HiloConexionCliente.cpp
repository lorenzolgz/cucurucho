//
// Created by camix on 9/6/20.
//

#include "HiloConexionCliente.h"

HiloConexionCliente::HiloConexionCliente(ConexionCliente *conexionCliente,
                                         ColaBloqueante<nlohmann::json> *colaMensajes) {
    HiloConexionCliente::conexionCliente = conexionCliente;
    HiloConexionCliente::colaMensajes = colaMensajes;

}


void HiloConexionCliente::run() {
	l->info("Comenzando a correr HiloConexionCliente");

    try {
        while (conexionCliente == nullptr) {
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
        while (true) {
            l->info("whileHiloConexionCliente");
            nlohmann::json mensajeRecibido = conexionCliente->recibirMensaje();
            l->info("recHiloConexionCliente " + mensajeRecibido.dump());
            colaMensajes->push(mensajeRecibido);
        }
    }
    catch(...){
        conexionCliente = nullptr;
        run();
    }

	l->info("Terminando de correr HiloConexionCliente");
}
