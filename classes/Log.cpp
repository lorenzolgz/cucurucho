//
// Created by camix on 16/4/20.
//

#include "Log.h"
#include "Configuracion.h"

#define INFO  nivel == "info"
#define DEBUG INFO or nivel == "debug"
#define ERROR DEBUG or nivel == "error"


Log::Log() {
    nivel = "";
}

void output(std::string estado_log, std::string mensaje){
    auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto timestamp = std::put_time(gmtime(&timenow), "%Y-%m-%d %H:%M:%S");
    std::cout << timestamp << estado_log << mensaje << std::endl;
}

void Log::error(std::string string) {
    if ( ERROR ) output(" - ERROR - ", string);
}

void Log::debug(std::string string) {
    if ( DEBUG ) output(" - WARNING - ", string);
}

void Log::info(std::string string) {
    if ( INFO ) output(" - INFO - ", string);
}

void Log::setConf(std::string string) {
    Log::nivel = string;
}

