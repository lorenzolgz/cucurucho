#ifndef CUCURUCHO_CONFIGURACIONPARSER_H
#define CUCURUCHO_CONFIGURACIONPARSER_H


#include <string>
#include "FondoConfiguracion.h"
#include <jsoncpp/json/json.h>
#include <list>

class ConfiguracionParser {
public:
    std::list<FondoConfiguracion*> parsearArchivoFondos(std::string rutaRelativa, int nivel);

private:
	void validarJsonGenerico(bool hayError, std::string mensaje);
    FondoConfiguracion* parsearFondo(Json::Value fondoJson, int nivel);
    std::list<FondoConfiguracion*> parsearFondos(Json::Value fondosConfiguracionJson, int nivel);
};


#endif //CUCURUCHO_CONFIGURACIONPARSER_H
