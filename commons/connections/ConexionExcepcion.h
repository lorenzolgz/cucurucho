//
// Created by javier on 12/6/20.
//

#ifndef CUCURUCHO_CONEXIONEXCEPCION_H
#define CUCURUCHO_CONEXIONEXCEPCION_H

#include <stdexcept>
#include <string>

class ConexionExcepcion : public std::runtime_error {
public:
    ConexionExcepcion() : runtime_error("Error de conexion") {}
};

#endif //CUCURUCHO_CONEXIONEXCEPCION_H
