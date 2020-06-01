//
// Created by camix on 16/4/20.
//

#ifndef CUCURUCHO_LOG_H
#define CUCURUCHO_LOG_H
#include <chrono>
#include <string>
#include <iostream>
#include <time.h>
#include <iomanip>
#include <fstream>
#include <experimental/filesystem>

class Log {
private:
	std::string homePath;
    std::string nivel = "error";
    char logEntrada [30]{};

public:
    Log(std::string basePath);

    void error(const std::string& string);
    void debug(const std::string& string);
    void info(const std::string& string);

    void setConf(std::string string);

    void output(const std::string& estado_log, const std::string& mensaje);
    static void cargar_log(std::string log, time_t timestamp, const std::string& estado, const std::string& msj);

    static bool confValida(std::string nivel);
};

extern Log* l;


#endif //CUCURUCHO_LOG_H
