#include "Log.h"

#include "string.h"
#include <utility>
#include <iostream>
#include <string.h>


#define DEBUG nivel == "debug"
#define INFO  DEBUG or nivel == "info"
#define ERROR INFO or nivel == "error"
#define RELATIVE_PATHLOGTIME "log-%y%m%d-%H%M%S.txt"
#define RELATIVE_PATHLOG "log.txt"
#define RELATIVE_HOME_PATH "/log/"

namespace fs = std::experimental::filesystem;

Log::Log(std::string basePath) {
	Log::homePath = "../" + basePath + RELATIVE_HOME_PATH;

    if (!fs::is_directory(homePath) || !fs::exists(homePath)) { // Check if src folder exists
        fs::create_directory(homePath); // create src folder
    }

    std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    std::string pathlogtime = homePath + RELATIVE_PATHLOGTIME;
	char pathlogthimeAsCharArray[pathlogtime.size() + 1];
	strcpy(pathlogthimeAsCharArray, pathlogtime.c_str());	// or pass &s[0]
    std::strftime(Log::logEntrada, 30, pathlogthimeAsCharArray , std::localtime(&t));
    std::fstream archivo;
    archivo.open(logEntrada , std::fstream::out);
    archivo.close();

    archivo.open(homePath + RELATIVE_PATHLOG , std::fstream::out);
    archivo.close();
}


void Log::output(const std::string& estado_log, const std::string& mensaje) {
	std::string pathlog = homePath + RELATIVE_PATHLOG;
    std::time_t timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    cargar_log(logEntrada, timenow, estado_log, mensaje);
    cargar_log(homePath + RELATIVE_PATHLOG, timenow, estado_log, mensaje);
}

void Log::error(const std::string& string) {
    if ( ERROR ) output(" - ERROR - ", string);
}

void Log::debug(const std::string& string) {
    // !!!! if ( DEBUG ) output(" - DEBUG - ", string);
}

void Log::info(const std::string& string) {
    if ( INFO ) output(" - INFO - ", string);
}

bool Log::confValida(std::string nivel) {
    return ERROR;
}

void Log::setConf(std::string string) {
    Log::nivel = std::move(string);
}

void Log::cargar_log(std::string log, time_t timestamp, const std::string& estado, const std::string& msj){
    std::fstream archivo;
    archivo.open(log , std::fstream::app);
    char horario[30];
    std::strftime(horario, 30, "%x %X" , std::localtime(&timestamp));
    archivo << horario << estado << msj << std::endl;
    // !!!!
	std::cout << horario << estado << msj << std::endl;
	archivo.flush();
    archivo.close();
}
