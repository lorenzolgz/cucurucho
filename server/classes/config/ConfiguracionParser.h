#ifndef CUCURUCHO_CONFIGURACIONPARSER_H
#define CUCURUCHO_CONFIGURACIONPARSER_H


#include <string>
#include "Configuracion.h"

class ConfiguracionParser {
public:
	Configuracion* parsearConfiguracion(std::string rutaJsonConfig);

private:
	Json::Value get(Json::Value value, std::string mensaje, bool requerido = true);
	void validarJsonNoNulo(Json::Value value, std::string mensaje);
	void validarJsonNoNegativo(Json::Value value, std::string mensaje);
	void validarJsonGenerico(bool hayError, std::string mensaje);

	EnemigosConfiguracion* parsearEnemigos(Json::Value enemigosJson, int nivel);
    std::string parsearFinalNivel(Json::Value imagenFinalJson);
    float parsearVelocidadNivel(Json::Value nivelJSON, int i);
    float parsearLargoNivel(Json::Value nivelJSON, int nivel);
    NivelConfiguracion* parsearNivel(Json::Value nivelJson, int nivel);

	std::list<NivelConfiguracion*> parsearNiveles(Json::Value nivelesJson);
};


#endif //CUCURUCHO_CONFIGURACIONPARSER_H
