#ifndef CUCURUCHO_FONDOCONFIGURACION_H
#define CUCURUCHO_FONDOCONFIGURACION_H


#include <string>

class FondoConfiguracion {
public:
	FondoConfiguracion(const std::string &archivo, double velocidad);

	const std::string &getArchivo() const;
	double getVelocidad() const;

private:
	std::string archivo;
	double velocidad;
};


#endif //CUCURUCHO_FONDOCONFIGURACION_H
