//
// Created by camix on 16/4/20.
//

#include "Log.h"

#include <utility>
#include "config/Configuracion.h"


#define DEBUG nivel == "debug"
#define INFO  DEBUG or nivel == "info"
#define ERROR INFO or nivel == "error"
#define PATHLOGTIME "../log/log-%y%m%d-%H%M.txt"
#define PATHLOG "../log/log.txt"
#define PATH "../log"

namespace fs = std::experimental::filesystem;

Log::Log() {

    if (!fs::is_directory(PATH) || !fs::exists(PATH)) { // Check if src folder exists
        fs::create_directory(PATH); // create src folder
    }

    std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::strftime(Log::logEntrada, 30, PATHLOGTIME , std::localtime(&t));
    std::fstream archivo;
    archivo.open(logEntrada , std::fstream::out);
    archivo.open(PATHLOG , std::fstream::out);
}


void Log::output(const std::string& estado_log, const std::string& mensaje) {
    std::time_t timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

    cargar_log(logEntrada, timenow, estado_log, mensaje);
    cargar_log(PATHLOG, timenow,estado_log, mensaje);
}

void Log::error(const std::string& string) {
    if ( ERROR ) output(" - ERROR - ", string);
}

void Log::debug(const std::string& string) {
    if ( DEBUG ) output(" - DEBUG - ", string);
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
    archivo.close();
}
