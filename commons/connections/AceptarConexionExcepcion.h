#ifndef CUCURUCHO_ACEPTARCONEXIONEXCEPCION_H
#define CUCURUCHO_ACEPTARCONEXIONEXCEPCION_H


#include <stdexcept>
#include <string>

class AceptarConexionExcepcion : public std::runtime_error {
public:
	AceptarConexionExcepcion() : runtime_error("Error al aceptar conexion") {}
};


#endif //CUCURUCHO_ACEPTARCONEXIONEXCEPCION_H
