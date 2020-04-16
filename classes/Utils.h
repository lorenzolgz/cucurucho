//
// Created by javier on 11/4/20.
//

#ifndef CPP_SANDBOX_UTILS_H
#define CPP_SANDBOX_UTILS_H

#include <SDL_render.h>
#include <string>

SDL_Texture * cargarTextura(SDL_Renderer* gRenderer, const std::string& path);

double cos_d(double angulo_d);
double sin_d(double angulo_d);
double to_d(double angulo_r);
double to_r(double angulo_d);

#endif //CPP_SANDBOX_UTILS_H
