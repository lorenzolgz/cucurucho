#ifndef CUCURUCHO_CONFIGURACIONPARSER_H
#define CUCURUCHO_CONFIGURACIONPARSER_H

#include <string>
#include "Configuracion.h"
#define FIN_ARCH '\0'

class ConfiguracionParser {
public:
	Configuracion* parsearConfiguracion(std::string rutaJsonConfig);

private:
	Json::Value get(Json::Value value, std::string mensaje, bool requerido = true);
	void validarJsonNoNulo(Json::Value value, std::string mensaje);
	void validarJsonNoNegativo(Json::Value value, std::string mensaje);
    void validarJsonGenerico(bool hayError, std::string mensaje);

	EnemigosConfiguracion* parsearEnemigos(Json::Value enemigosJson, int nivel);
    void parsearFinalNivel(Json::Value imagenFinalJson, char* fondosJson);
    float parsearVelocidadNivel(Json::Value nivelJSON, int i);
    float parsearLargoNivel(Json::Value nivelJSON, int nivel);
    NivelConfiguracion* parsearNivel(Json::Value nivelJson, int nivel);
    int parsearCantidadJugadores(Json::Value cantidadJson);

    std::list<NivelConfiguracion*> parsearNiveles(Json::Value nivelesJson);

    std::list<FondoConfiguracion *> parsearArchivoFondos(Json::Value jsonConfig, int nivel);

    static FondoConfiguracion *parsearFondo(Json::Value fondoJson, int nivel);

    std::list<FondoConfiguracion *> parsearFondos(Json::Value fondosConfiguracionJson, int nivel);
};


#endif //CUCURUCHO_CONFIGURACIONPARSER_H
