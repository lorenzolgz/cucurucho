//
// Created by camix on 16/4/20.
//

#include "Log.h"

Log::Log (){}

void output(std::string estado_log, std::string mensaje){
    auto timenow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    auto timestamp = std::put_time(gmtime(&timenow), "%Y-%m-%d %H:%M:%S");
    std::cout << timestamp << estado_log << mensaje << std::endl;
}

void Log::error(std::string mensaje) {
    output(" - ERROR - ", mensaje);
};

void Log::warning(std::string mensaje) {
    output(" - WARNING - ", mensaje);
};

void Log::info(std::string mensaje) {
    output(" - INFO - ", mensaje);
};