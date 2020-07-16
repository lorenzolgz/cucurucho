#ifndef CUCURUCHO_CONFIGURACIONPARSER_H
#define CUCURUCHO_CONFIGURACIONPARSER_H


#include <string>
#include "Configuracion.h"
#include <jsoncpp/json/json.h>
#include <list>

class ConfiguracionParser {
public:
    Configuracion *parsearConfiguracion(std::string rutaJsonConfig);

private:
	int parsearParametrosConexion(Json::Value root);
	std::string parsearNivelLog(Json::Value root);

	void validarJsonGenerico(bool hayError, std::string mensaje);
	void validarJsonNoNulo(Json::Value value, std::string campo);
    void validarJsonNoNegativo(Json::Value value, std::string campo);
};


#endif //CUCURUCHO_CONFIGURACIONPARSER_H
