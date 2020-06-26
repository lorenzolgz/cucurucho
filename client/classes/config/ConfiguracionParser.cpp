#include "ConfiguracionParser.h"
#include <queue>
#include <regex>
#include <string>
#include <list>
#include <jsoncpp/json/value.h>
#include "NivelConfiguracion.h"
#include "../../../commons/utils/Log.h"
#include "../../../commons/protocols/protocolo.h"


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

std::string parsearNivelLog(Json::Value root) {
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
void parsearParametrosConexion(Json::Value root, int& maxCola) {
    maxCola = MAX_COLA_CLIENTE;
    try {
        if (root["conexion"]["maxCola"].asInt() >= 1) {
            maxCola = root["conexion"]["maxCola"].asInt();
        }
    }
    catch(const std::exception& exc) {
        l->debug("Ocurrio un error al obtener la cantidad maxima de elementos para la cola. Usando valor de defecto.");
    }
}


Configuracion * ConfiguracionParser::parsearConfiguracion(std::string rutaJsonConfig){
    Json::Value jsonConfig;
    std::ifstream archivo(rutaJsonConfig);
    if (archivo.fail()){
        std::cout<<rutaJsonConfig<<" no direcciona estadosEnemigos un archivo JSON de configuracion"<<std::endl;
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

    int maxCola;
    parsearParametrosConexion(configuracionJson, maxCola);

    return new Configuracion(nivelLog, std_out, maxCola);
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

