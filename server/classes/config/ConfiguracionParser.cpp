#include "ConfiguracionParser.h"
#include <queue>
#include <regex>
#include <string>
#include <list>
#include "NivelConfiguracion.h"
#include "FondoConfiguracion.h"
#include "../model/Nivel.h"
#include "../../../commons/utils/Log.h"
#include "../../../commons/utils/Constantes.h"


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
		l->error(mensaje);
		throw std::exception();
	}
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
void parsearResolucion(const Json::Value &root, int &anchoPantalla, int &altoPantalla, int &escala) {
	anchoPantalla = PANTALLA_ANCHO;
	altoPantalla = PANTALLA_ALTO;
	escala = PANTALLA_ESCALA;
	return;
}

int ConfiguracionParser::parsearCantidadJugadores(Json::Value cantidadJson) {
    try {
        validarJsonNoNulo(cantidadJson, "Cantidad de jugadores");
        validarJsonGenerico(!cantidadJson.isNumeric(), "La cantidad de jugadores no es numerica");
        validarJsonGenerico(cantidadJson.asInt() < 1, "La cantidad de jugadores es menor a 1");
        validarJsonGenerico(cantidadJson.asInt() > MAX_JUGADORES, "La cantidad de jugadores es mayor a " + std::to_string(MAX_JUGADORES));
        return cantidadJson.asInt();
    } catch(const std::exception& exc) {
        l->error("Ocurrio un error al cargar la cantidad de jugadores");
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
		l->error("Ocurrio un error al parsear las cantidades de enemigos para el nivel " + std::to_string(nivel));
		throw exc;
	}
}

void ConfiguracionParser::parsearFinalNivel(Json::Value nivelJSON, char* fondosJson) {
    strcpy(fondosJson, nivelJSON["fin"].asString().c_str());
}

float ConfiguracionParser::parsearVelocidadNivel(Json::Value nivelJSON, int nivel) {
    try {
        Json::Value velocidad = nivelJSON["velocidad"];
		validarJsonNoNulo(velocidad, "velociad del nivel " + std::to_string(nivel));
		validarJsonNoNegativo(velocidad, "velociad del nivel " + std::to_string(nivel));

        return velocidad.asFloat();
    } catch (const std::exception &exc) {
        l->error("Ocurrio un error al parsear la velocidad para el nivel nivel " + std::to_string(nivel));
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
        l->error("Ocurrio un error al parsear la velocidad para el nivel nivel " + std::to_string(nivel));
        throw exc;
    }
}

FondoConfiguracion* ConfiguracionParser::parsearFondo(Json::Value fondoJson, int nivel) {
    try {
        char archivo[LARGO_PATH];
        strcpy(archivo, fondoJson["archivo"].asString().c_str());
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

std::list<FondoConfiguracion*> ConfiguracionParser::parsearArchivoFondos(Json::Value jsonConfig, int nivel) {
    try {
        std::string rutaCarpetaConfig = "../server/config/";

        std::string rutaRelativa = jsonConfig.asString();
        if (!rutaRelativa.compare("")) {
            l->error("No se halló una ruta para el archivo de fondos");
            throw std::exception();
        }
        std::string rutaFondos = rutaCarpetaConfig += rutaRelativa;
        std::ifstream archivo(rutaFondos);
        if (archivo.fail()) {
            l->error(rutaFondos += " no direcciona estadosEnemigos un archivo JSON de fondos");
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


NivelConfiguracion* ConfiguracionParser::parsearNivel(Json::Value nivelJson, int nivel) {
	try {
		    auto *enemigos = parsearEnemigos(nivelJson["enemigos"], nivel);
		    char finNivel[LARGO_PATH];
		    parsearFinalNivel(nivelJson, finNivel);
            auto velocidad = parsearVelocidadNivel(nivelJson, nivel);
            auto largo = parsearLargoNivel(nivelJson, nivel);

            std::list<FondoConfiguracion*> fondos;

            //Validación de jsons de fondos
            try {
                fondos = parsearArchivoFondos(nivelJson["archivoFondos"], nivel);
            }
            catch(const std::exception &exc){
                std::string rutaJsonFondos = nivelJson["archivoFondos"].asString();
                l->error("Ocurrio un error al parsear el archivo de configuracion \"" + rutaJsonFondos + "\" por favor revise que este escrito correctamente");
                throw exc;
            }

	    	return new NivelConfiguracion(fondos, enemigos, finNivel, velocidad, largo);
	    }
	catch(const std::exception &exc) {
	        l->error("Ocurrio un error al parsear el nivel " + std::to_string(nivel));
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
		l->error("Error al parsear niveles");
		throw exc;
	}
}

// Estos parametros son opcionales. Si no existen en el JSON o son invalidos no deberian romper la configuracion
void parsearParametrosConexion(Json::Value root, int& maxColaEmisora, int& maxColaReceptora) {
    maxColaEmisora = MAX_COLA_EMISORA_SERVIDOR;
    maxColaReceptora = MAX_COLA_RECEPTORA_SERVIDOR;
    try {
        if (root["conexion"]["maxColaEmisora"].asInt() >= 1) {
            maxColaEmisora = root["conexion"]["maxColaEmisora"].asInt();
        }
        if (root["conexion"]["maxColaEmisora"].asInt() >= 1) {
            maxColaReceptora = root["conexion"]["maxColaReceptora"].asInt();
        }
    }
    catch(const std::exception& exc) {
        l->debug("Ocurrio un error al obtener la cantidad maxima de elementos para la cola. Usando valor de defecto.");
    }
}


Configuracion* ConfiguracionParser::parsearConfiguracion(std::string rutaJsonConfig){
	Json::Value jsonConfig;
	std::ifstream archivo(rutaJsonConfig);
	if (archivo.fail()){
		l->error(rutaJsonConfig +=  " no direcciona estadosEnemigos un archivo JSON de configuracion");
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
		l->error("Ocurrio un error al parsear el archivo de configuracion \"" + rutaJsonConfig + "\" por favor revise que este escrito correctamente");
		l->error("Referencia de la libreria: " + mensajeUnaLinea);
		throw std::exception();
	}

	int altoPantalla;
	int anchoPantalla;
	int escala;
	int cantidadJugadores;
	std::map<int, std::queue <int>> enemigos;
	std::string nivelLog;
	Json::Value fondosPorNivel;
	std::list<NivelConfiguracion*> niveles;

	Json::Value configuracionJson = jsonConfig["configuracion"];
	validarJsonNoNulo(configuracionJson, "configuracion");

	parsearResolucion(configuracionJson["resolucion"], anchoPantalla, altoPantalla, escala);

    cantidadJugadores = parsearCantidadJugadores(configuracionJson["cantidadJugadores"]);

	nivelLog = parsearNivelLog(configuracionJson);
	niveles = parsearNiveles(configuracionJson["niveles"]);

    bool std_out = configuracionJson["log"]["std_out"].asBool();

    int maxColaEmisora, maxColaReceptora;
    parsearParametrosConexion(configuracionJson, maxColaEmisora, maxColaReceptora);

	return new Configuracion(altoPantalla, anchoPantalla, escala, nivelLog, niveles, cantidadJugadores, std_out,
                             maxColaEmisora, maxColaReceptora);
}