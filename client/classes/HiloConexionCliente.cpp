//
// Created by camix on 9/6/20.
//

#include "HiloConexionCliente.h"

HiloConexionCliente::HiloConexionCliente(ColaBloqueante<nlohmann::json> *colaMensajes,
                                         IniciadorComunicacion* iniciadorComunicacion) {
    HiloConexionCliente::conexionCliente = nullptr;
    HiloConexionCliente::colaMensajes = colaMensajes;
    HiloConexionCliente::iniciadorComunicacion = iniciadorComunicacion;
    HiloConexionCliente::activo = false;
}


void HiloConexionCliente::run() {
    activo = true;
	l->info("Comenzando a correr HiloConexionCliente");
    conexionCliente = iniciadorComunicacion->conectar();

    try {
        while (activo && conexionCliente != nullptr) {
            l->info("whileHiloConexionCliente");
            nlohmann::json mensajeRecibido = conexionCliente->recibirMensaje();
            l->info("recHiloConexionCliente " + mensajeRecibido.dump());
            colaMensajes->push(mensajeRecibido);
        }
    } catch (const std::exception &exc) {
        cerrarConexion();
        l->info("Error en HiloConexionCliente " + std::string(exc.what()));
    }

    activo = false;
	l->info("Terminando de correr HiloConexionCliente");
}

void HiloConexionCliente::cerrarConexion() {
    if (conexionCliente != nullptr) {
        conexionCliente->cerrar();
        conexionCliente = nullptr;
    }
    activo = false;
}

bool HiloConexionCliente::isActivo() const {
    return activo;
}
