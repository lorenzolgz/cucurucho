#include "ConfiguracionParser.h"
#include <queue>
#include <regex>
#include <string>
#include "NivelConfiguracion.h"
#include "../model/Nivel.h"
#include "../Log.h"

Json::Value ConfiguracionParser::get(Json::Value value, std::string mensaje, bool requerido) {
	Json::Value campo = value["mensaje"];
	// Todo validar si es necesario, paja lo del mensaje
	return campo;
}

void ConfiguracionParser::validarJsonNoNulo(Json::Value value, std::string campo) {
	validarJsonGenerico(value.isNull(), "Campo nulo: " + campo);
}

void ConfiguracionParser::validarJsonNoNegativo(Json::Value value, std::string campo) {
	validarJsonGenerico(value.asInt64() < 0 || value.asFloat() < 0, "Campo negativo: " + campo);
}

void ConfiguracionParser::validarJsonGenerico(bool hayError, std::string mensaje) {
	if (hayError) {
		l.error(mensaje);
		throw std::exception();
	}
}

std::string parsearNivelLog(Json::Value root) {
	try {
		std::string nivelLog = root["log"]["nivel"].asString();
		if (!nivelLog.compare("")){
			l.error("No se hayó un nivel de log");
			throw std::exception();
		}
		if (nivelLog.compare("error") && nivelLog.compare("info") && nivelLog.compare("debug")){
			l.error("Se intento setear un nivel de log invalido. Los valores validos son 'debug', 'info' o 'error'");
			throw std::exception();
		}
		return nivelLog;
	}
	catch(const std::exception& exc) {
		l.error("Ocurrio un error al obtener el nivel de logging");
		throw exc;
	}
}
void parsearResolucion(const Json::Value &root, int &anchoPantalla, int &altoPantalla, int &escala) {
	anchoPantalla = PANTALLA_ANCHO;
	altoPantalla = PANTALLA_ALTO;
	escala = 1;
	return;

	try {
		Json::Value resolucionJson = root["resolucion"];
		altoPantalla = resolucionJson["alto"].asInt64();
		anchoPantalla = resolucionJson["ancho"].asInt64();
		escala = resolucionJson["escala"].asInt64();

		if (!altoPantalla) {
			l.error("No se halló un alto de pantalla");
			throw std::exception();
		}
		if (altoPantalla < 100) {
			l.error("Se intento setear un tamaño de pantalla muy pequeño");
			throw std::exception();
		}
		if (!anchoPantalla){
			l.error("No se halló un ancho de pantalla");
			throw std::exception();
		}
		if (anchoPantalla < 100){
			l.error("Intento setearse un ancho de pantalla muy pequeño");
			throw std::exception();
		}
		if (!escala){
			l.error("No se halló una escala de pantalla");
			throw std::exception();
		}
		if (escala < 0){
			l.error("Intento setearse una escala de pantalla negativa");
			throw std::exception();
		}
	}
	catch(const std::exception& exc) {
		l.error("Ocurrio un error al cargar la resolucion de pantalla");
		throw exc;
	}
}

std::list<FondoConfiguracion*> ConfiguracionParser::parsearArchivoFondos(Json::Value jsonConfig, int nivel) {
	try {
		std::string rutaCarpetaConfig = "../config/";

		std::string rutaRelativa = jsonConfig.asString();
		if (!rutaRelativa.compare("")) {
			l.error("No se halló una ruta para el archivo de fondos");
			throw std::exception();
		}
		std::string rutaFondos = rutaCarpetaConfig += rutaRelativa;
		std::ifstream archivo(rutaFondos);
		if (archivo.fail()) {
			l.error(rutaFondos += " no direcciona a un archivo JSON de fondos");
			throw std::exception();
		}

		Json::Value jsonFondos;
		archivo >> jsonFondos;

		return parsearFondos(jsonFondos, nivel);
	} catch (const std::exception &exc) {
		l.error("Ocurrio un error al obtener las rutas de las imagenes de fondo");
		throw exc;
	}
}

EnemigosConfiguracion* ConfiguracionParser::parsearEnemigos(Json::Value enemigosJson, int nivel) {
	try {
		Json::Value clase1Json = enemigosJson["clase1"];
		validarJsonNoNulo(clase1Json, "Enemigos de clase1 del nivel " + std::to_string(nivel));
		validarJsonNoNegativo(clase1Json, "Enemigos de clase1 del nivel " + std::to_string(nivel));

		Json::Value clase2Json = enemigosJson["clase2"];
		validarJsonNoNulo(clase2Json,"Enemigos de clase2 del nivel " + std::to_string(nivel));
		validarJsonNoNegativo(clase2Json, "Enemigos de clase2 del nivel " + std::to_string(nivel));

		return new EnemigosConfiguracion(clase1Json.asInt64(), clase2Json.asInt64());
	} catch (const std::exception &exc) {
		l.error("Ocurrio un error al parsear las cantidades de enemigos para el nivel " + to_string(nivel));
		throw exc;
	}
}

FondoConfiguracion* ConfiguracionParser::parsearFondo(Json::Value fondoJson, int nivel) {
	try {
		std::string archivo = fondoJson["archivo"].asString();
		double velocidad = fondoJson["velocidad"].asDouble();

		return new FondoConfiguracion(archivo, velocidad);
	} catch (const std::exception &exc) {
		l.error("Ocurrio un error al parsear uno de los fondos del nivel " + to_string(nivel) +
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

std::string ConfiguracionParser::parsearFinalNivel(Json::Value nivelJSON) {
    std::string fondosJson = nivelJSON["fin"].asString();
    return fondosJson;
}

float ConfiguracionParser::parsearVelocidadNivel(Json::Value nivelJSON, int nivel) {
    try {
        Json::Value velocidad = nivelJSON["velocidad"];
		validarJsonNoNulo(velocidad, "velociad del nivel " + std::to_string(nivel));
		validarJsonNoNegativo(velocidad, "velociad del nivel " + std::to_string(nivel));

        return velocidad.asFloat();
    } catch (const std::exception &exc) {
        l.error("Ocurrio un error al parsear la velocidad para el nivel nivel " + to_string(nivel));
        throw exc;
    }
}

float ConfiguracionParser::parsearLargoNivel(Json::Value nivelJSON, int nivel) {
    try {
        Json::Value velocidad = nivelJSON["largo"];
		validarJsonNoNulo(velocidad, "largo del nivel " + std::to_string(nivel));
		validarJsonNoNegativo(velocidad, "largo del nivel " + std::to_string(nivel));

        return velocidad.asFloat();
    } catch (const std::exception &exc) {
        l.error("Ocurrio un error al parsear la velocidad para el nivel nivel " + to_string(nivel));
        throw exc;
    }
}

NivelConfiguracion* ConfiguracionParser::parsearNivel(Json::Value nivelJson, int nivel) {
	try {
		auto *enemigos = parsearEnemigos(nivelJson["enemigos"], nivel);
		auto fondos = parsearArchivoFondos(nivelJson["archivoFondos"], nivel);
		auto finNivel = parsearFinalNivel(nivelJson);
        auto velocidad = parsearVelocidadNivel(nivelJson, nivel);
        auto largo = parsearLargoNivel(nivelJson, nivel);

		return new NivelConfiguracion(fondos, enemigos, finNivel, velocidad, largo);
	} catch (const std::exception &exc) {
		l.error("Ocurrio un error al parsear el nivel " + to_string(nivel));
		throw exc;
	}
}

std::list<NivelConfiguracion*> ConfiguracionParser::parsearNiveles(Json::Value nivelesJson) {
	try {
		std::list<NivelConfiguracion *> nivelesConfiguracion;

		int i = 0;
		for (Json::Value nivelJson : nivelesJson) {
			i += 1;
			NivelConfiguracion *nivelConfiguracion = parsearNivel(nivelJson, i);
			nivelesConfiguracion.push_back(nivelConfiguracion);
		}

		return nivelesConfiguracion;
	} catch (const std::exception &exc) {
		l.error("Error al parsear niveles");
		throw exc;
	}
}

Configuracion* ConfiguracionParser::parsearConfiguracion(std::string rutaJsonConfig){
	Json::Value jsonConfig;
	std::ifstream archivo(rutaJsonConfig);
	if (archivo.fail()){
		l.error(rutaJsonConfig +=  " no direcciona a un archivo JSON de configuracion");
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
		l.error("Ocurrio un error al parsear el archivo de configuracion \"" + rutaJsonConfig + "\" por favor revise que este escrito correctamente");
		l.error("Referencia de la libreria: " + mensajeUnaLinea);
		throw std::exception();
	}

	int altoPantalla;
	int anchoPantalla;
	int escala;
	map<int, queue <int>> enemigos;
	std::string nivelLog;
	Json::Value fondosPorNivel;
	std::list<NivelConfiguracion*> niveles;

	Json::Value configuracionJson = jsonConfig["configuracion"];
	validarJsonNoNulo(configuracionJson, "configuracion");

	parsearResolucion(configuracionJson["resolucion"], anchoPantalla, altoPantalla, escala);
	nivelLog = parsearNivelLog(configuracionJson);
	niveles = parsearNiveles(configuracionJson["niveles"]);

	return new Configuracion(altoPantalla, anchoPantalla, escala, nivelLog, niveles);
}
