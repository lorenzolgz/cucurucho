#include "ConfiguracionParser.h"
#include <queue>
#include <regex>
#include <string>
#include <list>
#include <jsoncpp/json/value.h>
#include "NivelConfiguracion.h"
#include "../../../commons/utils/Log.h"


std::list<FondoConfiguracion*> ConfiguracionParser::parsearArchivoFondos(std::string rutaRelativa, int nivel) {
	try {
		std::string rutaCarpetaConfig = "../config/";

		if (!rutaRelativa.compare("")) {
			l->error("No se halló una ruta para el archivo de fondos");
			throw std::exception();
		}
		std::string rutaFondos = rutaCarpetaConfig += rutaRelativa;
		std::ifstream archivo(rutaFondos);
		if (archivo.fail()) {
			l->error(rutaFondos += " no direcciona a un archivo JSON de fondos");
			throw std::exception();
		}

		Json::Value jsonFondos;

		//Validación de sintaxis de json de fondos
		try {
		    archivo >> jsonFondos;
		}
        catch(Json::Exception const& a){
            const std::string mensaje(a.what());
            std::regex caracterIgnorado("\n+");
            auto mensajeUnaLinea = std::regex_replace(mensaje, caracterIgnorado, "");
            l->error("Referencia de la libreria: " + mensajeUnaLinea);
            throw a;
        }

		return parsearFondos(jsonFondos, nivel);
	} catch (const std::exception &exc) {
		l->error("Ocurrio un error al obtener las rutas de las imagenes de fondo");
		throw exc;
	}
}

FondoConfiguracion* ConfiguracionParser::parsearFondo(Json::Value fondoJson, int nivel) {
	try {
		std::string archivo = fondoJson["archivo"].asString();
		double velocidad = fondoJson["velocidad"].asDouble();

		return new FondoConfiguracion(archivo, velocidad);
	} catch (const std::exception &exc) {
		l->error("Ocurrio un error al parsear uno de los fondos del nivel " + std::to_string(nivel) +
		". Probablemente uno de los valores pasados no fue un entero");
		throw exc;
	}
}

std::list<FondoConfiguracion*> ConfiguracionParser::parsearFondos(Json::Value fondosConfiguracionJson, int nivel) {
	Json::Value fondosJson = fondosConfiguracionJson["fondos"];
	std::list<FondoConfiguracion*> fondosConfiguracion;

	for(Json::Value fondoJson : fondosJson) {
		FondoConfiguracion* fondoConfiguracion = parsearFondo(fondoJson, nivel);
		fondosConfiguracion.push_back(fondoConfiguracion);
	}

	return fondosConfiguracion;
}

