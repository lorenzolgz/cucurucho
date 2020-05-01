
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <queue>
#include <regex>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <jsoncpp/json/json.h>
#include "classes/model/Jugador.h"
#include "classes/Log.h"
#include "classes/Configuracion.h"
#include "classes/GraphicRenderer.h"
#include "classes/model/Nivel.h"


//The window we'll be rendering to
SDL_Window* gWindow = nullptr;

Configuracion* config;

Log l = Log();

std::string parsearNivelLog(Json::Value root) {
	try {
		std::string nivelLog = root["configuracion"]["log"]["nivel"].asString();
		if (!nivelLog.compare("")){
			l.error("No se hayó un nivel de log");
			throw std::exception();
		}
		if (nivelLog.compare("error") && nivelLog.compare("info") && nivelLog.compare("debug")){
			l.error("Se intento setear un nivel de log invalido");
			throw std::exception();
		}
		return nivelLog;
	}
	catch(const std::exception& exc) {
		l.error("Ocurrio un error al obtener el nivel de logging");
		throw exc;
	}
}

map<int, queue <int>> parsearEnemigos(const Json::Value &root) {
    map<int, queue <int>> mapEnemigosPorNivel;

    try {
        Json::Value enemigosPorNivel = root["configuracion"]["enemigosPorNivel"];

        int nivelActual = 1;
        Json::Value entradaNivel = enemigosPorNivel[std::to_string(nivelActual)];

        // Mientras haya entradas de nivel en el JSON
        while (!entradaNivel.isNull()){
            // Cola a guardar en el diccionario de enemigos
            queue <int> enemigos;

            // Leyendo enemigos tipo uno
            Json::Value enemigosUno = entradaNivel["tipoUno"];
            if (enemigosUno.isNull()) {
                l.error("No se halló la cantidad de enemigos uno para el nivel " + std::to_string(nivelActual));
                throw std::exception();
            }
            if (enemigosUno.asInt64() < 0) {
                l.error("Se halló una cantidad de enemigos tipo uno negativa para el nivel " + std::to_string(nivelActual));
                throw std::exception();
            }

            // Leyendo enemigos tipo dos
            Json::Value enemigosDos = entradaNivel["tipoDos"];
            if (enemigosDos.isNull()) {
                l.error("No se halló la cantidad de enemigos dos para el nivel " + std::to_string(nivelActual));
                throw std::exception();
            }
            if (enemigosDos.asInt64() < 0) {
                l.error("Se halló una cantidad de enemigos tipo dos negativa para el nivel " + std::to_string(nivelActual));
                throw std::exception();
            }

            // Cargando en la cola
            enemigos.push(enemigosUno.asInt64());
            enemigos.push(enemigosDos.asInt64());

            // Guardo enemigos
            mapEnemigosPorNivel.insert({nivelActual, enemigos});

            // Paso al nivel siguiente
            nivelActual++;
            entradaNivel =  enemigosPorNivel[std::to_string(nivelActual)];
        }
	}
	catch(const std::exception& exc) {
		l.error("Ocurrio un error al obtener la cantidad de enemigos");
		throw exc;
	}

	return mapEnemigosPorNivel;
}

void parsearResolucion(const Json::Value &root, int &altoPantalla, int &anchoPantalla, int &escala) {
	try {
		altoPantalla = root["configuracion"]["resolucion"]["alto"].asInt64();
		anchoPantalla = root["configuracion"]["resolucion"]["ancho"].asInt64();
		escala = root["configuracion"]["resolucion"]["escala"].asInt64();

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

Json::Value parsearFondos(Json::Value jsonConfig) {
	std::string rutaCarpetaConfig = "../config/";
	Json::Value jsonFondos;
	Json::Value fondosPorNivel;

	try {
		std::string rutaRelativa = jsonConfig["configuracion"]["rutaFondos"].asString();
		if (!rutaRelativa.compare("")){
			l.error("No se halló una ruta para el archivo de fondos");
			throw std::exception();
		}
		std::string rutaFondos = rutaCarpetaConfig += rutaRelativa;
		std::ifstream archivo(rutaFondos);
		if (archivo.fail()){
			l.error(rutaFondos +=  " no direcciona a un archivo JSON de fondos");
			throw std::exception();
		}
		archivo >> jsonFondos;
		fondosPorNivel = jsonFondos;
	} catch(const std::exception& exc){
		l.error("Ocurrio un error al obtener las rutas de las imagenes de fondo");
		throw exc;
	}

	return fondosPorNivel;
}

Configuracion* parsearConfiguracion(std::string rutaJsonConfig){
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

	parsearResolucion(jsonConfig, altoPantalla, anchoPantalla, escala);
	enemigos = parsearEnemigos(jsonConfig);
	nivelLog = parsearNivelLog(jsonConfig);
	fondosPorNivel = parsearFondos(jsonConfig);

	return new Configuracion(altoPantalla, anchoPantalla, escala, enemigos, nivelLog, fondosPorNivel);
}

void informarConfiguracion(Configuracion* config){
	l.info("Alto pantalla: " + std::to_string(config->getAltoPantalla()));
	l.info("Ancho pantalla: " + std::to_string(config->getAnchoPantalla()));
	l.info("Escala pantalla: " + std::to_string(config->getEscalaPantalla()));
	std::cout << "Cantidad de tipos de enemigos cargados en Nivel 1: " << config->getEnemigosNivel(1).size() << std::endl;
    std::cout << "Cantidad de tipos de enemigos cargados en Nivel 2: " << config->getEnemigosNivel(2).size() << std::endl;
	l.info("Nivel de Log: " + config->getNivelLog());
}


void configurar(){
	try {
		config = parsearConfiguracion("../config/config.json");
	}
	catch (const std::exception& exc) {
		config = parsearConfiguracion("../config/backup.json");

		// Solo se loguean las excepciones que tengan un what() para poder dar mas info
		if ((exc.what()!= NULL) && (exc.what()[0] == '\0')){
			l.error(exc.what());
		}
		l.error("Ocurrió un error al leer el archivo de configuración, se usará el de backup");
	}
	l.setConf(config->getNivelLog());
	informarConfiguracion(config);
}


bool init() {
	int anchoPantalla = config->getAnchoPantalla();
	int altoPantalla = config->getAltoPantalla();
	int escalaPantalla = config->getEscalaPantalla();

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		l.error((std::string("No se logro inicializar SDL! SDL_Error: %s\n") + SDL_GetError()));
		return false;
	}

	// Set texture filtering to linear
	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		l.debug("No se habilito el filro de la textura linear");
	}

	//Initialize SDL_image
	if (!(IMG_Init(IMG_INIT_PNG))) {
		l.error(std::string("No se logro inicializar SDL_image. SDL_image Error: ") + IMG_GetError());
		return false;
	}

	gWindow = SDL_CreateWindow("cpp sandbox", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							   anchoPantalla * escalaPantalla, altoPantalla * escalaPantalla, SDL_WINDOW_SHOWN);
	if (gWindow == nullptr) {
		l.error(std::string("La Ventana no creo correctamente! SDL_Error: ") + SDL_GetError());
		return false;
	}
	//Get window surface

	SDL_Renderer* gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (gRenderer == nullptr) {
		l.error(std::string("El Renderer no se creo correctamente! SDL_Error: ") + SDL_GetError());
		return false;
	}
	GraphicRenderer::setInstance(gRenderer);

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");
	SDL_RenderSetScale(gRenderer, escalaPantalla, escalaPantalla);

	l.info("La ventana se creo correctamente");
	return true;
}


void close() {
	//Deallocate textures
	SDL_Renderer* gRenderer = GraphicRenderer::getInstance();
	SDL_DestroyRenderer(gRenderer);

	//Destroy window
	SDL_DestroyWindow(gWindow);

	//Free Configuration
	delete(config);

	l.info("Se libero toda la memoria ( todo:( )");
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
	l.info("La ventana se cerro correctamente");
}

void mainLoop() {
	bool quit = false;
	SDL_Event e;

	int anchoPantalla = config->getAnchoPantalla();
	int altoPantalla = config->getAltoPantalla();

	Jugador* jugador = new Jugador(anchoPantalla / 8, altoPantalla / 2);
	Nivel* nivel = new Nivel(config, jugador, 1000, 100);
	nivel->crearEnemigos(config);



	l.info("Los objetos fueron inicializados correctamente a partir de los datos de la configuracion inicial");

	while (!quit) {
		//Handle events on queue
		while (SDL_PollEvent( &e ) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}

		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		jugador->calcularVectorVelocidad(currentKeyStates[SDL_SCANCODE_UP],
										 currentKeyStates[SDL_SCANCODE_DOWN],
										 currentKeyStates[SDL_SCANCODE_LEFT],
										 currentKeyStates[SDL_SCANCODE_RIGHT]);

		SDL_Renderer* gRenderer = GraphicRenderer::getInstance();
		//Clear screen
		SDL_RenderClear(gRenderer);

		//Render texture to screen
		nivel->tick();

		//Update screen
		SDL_RenderPresent(gRenderer);
	}
}


int main(int, char**) {
	std::srand(std::time(NULL)); //use current time as seed for random generator
	configurar();
	// Inicializa con la configuracion
	if (!init()) return 1;

	// Comienza el juego con la configuracion
	mainLoop();

	close();
	return 0;
}
