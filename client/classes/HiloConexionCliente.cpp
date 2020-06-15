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

    try{
        while (true) {
            l->info("whileHiloConexionCliente");
            nlohmann::json mensajeRecibido = conexionCliente->recibirMensaje();
            l->info("recHiloConexionCliente " + mensajeRecibido.dump());
            colaMensajes->push(mensajeRecibido);
        }
    }
    catch(...){
        std::cout << "Ocurrio un error en el hiloConexionCliente" << std::endl;
    }

	l->info("Terminando de correr HiloConexionCliente");
}
