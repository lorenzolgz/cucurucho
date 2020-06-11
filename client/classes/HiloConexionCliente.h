//
// Created by camix on 9/6/20.
//

#ifndef CUCURUCHO_HILOCONEXIONCLIENTE_H
#define CUCURUCHO_HILOCONEXIONCLIENTE_H


#include <jsoncpp/json/json.h>
#include "../../commons/Thread.h"
#include "../../commons/connections/ConexionCliente.h"
#include "../../commons/ColaBloqueante.h"

class HiloConexionCliente : public Thread {
public:
    HiloConexionCliente(ConexionCliente* conexionCliente, ColaBloqueante<nlohmann::json>* colaComandos);
    void run() override;

private:
    ConexionCliente* conexionCliente;
    ColaBloqueante<nlohmann::json>* colaComandos;
};

#endif //CUCURUCHO_HILOCONEXIONCLIENTE_H
