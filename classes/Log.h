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


class Log {
public:
    Log();
    void error(std::string mensaje);
    void warning(std::string mensaje);
    void info(std::string mensaje);


};

extern Log l;

#endif //CUCURUCHO_LOG_H
