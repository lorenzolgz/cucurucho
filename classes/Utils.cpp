//
// Created by javier on 11/4/20.
//

#include <SDL_render.h>
#include "Utils.h"


#define PI 3.14159265358979323846


double cos_d(double angulo_d) {
    return cos(to_r(angulo_d));
}


double sin_d(double angulo_d) {
    return sin(to_r(angulo_d));
}


double to_r(double angulo_d) {
    return angulo_d * PI / 180;
}


double to_d(double angulo_r) {
    return angulo_r / PI * 180;
}
