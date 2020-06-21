//
// Created by camix on 9/6/20.
//

#ifndef CUCURUCHO_HILOCONEXIONCLIENTE_H
#define CUCURUCHO_HILOCONEXIONCLIENTE_H


#include <jsoncpp/json/json.h>
#include "../../commons/Thread.h"
#include "../../commons/connections/ConexionCliente.h"
#include "../../commons/ColaBloqueante.h"
#include "../../commons/connections/IniciadorComunicacion.h"

class HiloConexionCliente : public Thread {

public:
    HiloConexionCliente(ColaBloqueante<nlohmann::json> *colaMensajes,
                        IniciadorComunicacion* iniciadorComunicacion);
    ConexionCliente* conexionCliente;
    IniciadorComunicacion* iniciadorComunicacion;
    void run() override;

    void cerrarConexion();

    bool isActivo() const;

private:
    ColaBloqueante<nlohmann::json>* colaMensajes;
    bool activo;
};

#endif //CUCURUCHO_HILOCONEXIONCLIENTE_H
