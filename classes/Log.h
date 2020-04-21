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
#include "Configuracion.h"


class Log {
private:
    std::string nivel;
public:
    Log();

    void error(std::string string);
    void debug(std::string string);
    void info(std::string string);

    void setConf(std::string string);

};

extern Log l;


#endif //CUCURUCHO_LOG_H
