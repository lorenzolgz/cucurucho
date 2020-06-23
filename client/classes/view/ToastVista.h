//
// Created by javier on 3/6/20.
//

#ifndef CUCURUCHO_TOASTVISTA_H
#define CUCURUCHO_TOASTVISTA_H


#include <string>
#include "TextoVista.h"
#include <vector>

class ToastVista {
public:
    ToastVista();
    void render();
    void setTexto(std::string texto, int tiempo, int color);

private:
    int contador;
    int tiempo;
    int textoMaximo;
    Vector posicion;
    Vector posicionFinal;
    std::vector<TextoVista*> textos;
};


#endif //CUCURUCHO_TOASTVISTA_H
