#include "ConfiguracionParser.h"
#include <queue>
#include <regex>
#include <string>
#include <list>
#include <jsoncpp/json/value.h>
#include "../../../commons/utils/Log.h"
#include "../../../commons/protocols/protocolo.h"

Configuracion * ConfiguracionParser::parsearConfiguracion(std::string rutaJsonConfig){
	Json::Value jsonConfig;
	std::ifstream archivo(rutaJsonConfig);
	if (archivo.fail()){
		std::cout<<rutaJsonConfig<<" no direcciona a un archivo JSON de configuracion"<<std::endl;
		throw std::exception();
	}

	try {
		archivo >> jsonConfig;
	}
	catch(Json::Exception const& a){
		// Acomodo el mensaje de la libreria para que quede de una sola linea
		const std::string mensaje(a.what());
		std::regex caracterIgnorado("\n+");
		auto mensajeUnaLinea = std::regex_replace(mensaje, caracterIgnorado, "");
		std::cout<<"Ocurrio un error al parsear el archivo de configuracion \"" + rutaJsonConfig + "\" por favor revise que este escrito correctamente"<<std::endl;
		std::cout<<"Referencia de la libreria: " + mensajeUnaLinea<<std::endl;
		throw std::exception();
	}

	std::string nivelLog;

	Json::Value configuracionJson = jsonConfig["configuracion"];
	validarJsonNoNulo(configuracionJson, "configuracion");

	nivelLog = parsearNivelLog(configuracionJson);

	bool std_out = configuracionJson["log"]["std_out"].asBool();
	int maxCola = parsearParametrosConexion(configuracionJson);

	return new Configuracion(nivelLog, std_out, maxCola);
}

std::string ConfiguracionParser::parsearNivelLog(Json::Value root) {
    try {
        std::string nivelLog = root["log"]["nivel"].asString();
        if (!nivelLog.compare("")){
            l->error("No se hayó un nivel de log");
            throw std::exception();
        }
        if (nivelLog.compare("error") && nivelLog.compare("info") && nivelLog.compare("debug")){
            l->error("Se intento setear un nivel de log invalido. Los valores validos son 'debug', 'info' o 'error'");
            throw std::exception();
        }
        return nivelLog;
    }
    catch(const std::exception& exc) {
        l->error("Ocurrio un error al obtener el nivel de logging");
        throw exc;
    }
}

// Estos parametros son opcionales. Si no existen en el JSON o son invalidos no deberian romper la configuracion
int ConfiguracionParser::parsearParametrosConexion(Json::Value root) {
	int maxCola = MAX_COLA_CLIENTE;
	try {
		if (root["conexion"]["maxCola"].asInt() >= 1) {
			maxCola = root["conexion"]["maxCola"].asInt();
		}
	}
	catch (const std::exception &exc) {
		l->debug("Ocurrio un error al obtener la cantidad maxima de elementos para la cola. Usando valor de defecto.");
	}

	return maxCola;
}

void ConfiguracionParser::validarJsonNoNulo(Json::Value value, std::string ruta) {
    validarJsonGenerico(value.isNull(), "Campo nulo: " + ruta);
}

void ConfiguracionParser::validarJsonGenerico(bool hayError, std::string mensaje) {
    if (hayError) {
        l->error(mensaje);
        throw std::exception();
    }
}

void ConfiguracionParser::validarJsonNoNegativo(Json::Value value, std::string campo) {
    validarJsonGenerico(value.asInt64() < 0 || value.asFloat() < 0, "Campo negativo: " + campo);
}

