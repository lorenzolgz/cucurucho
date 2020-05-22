//
// Created by javier on 21/5/20.
//

#ifndef CUCURUCHO_COLORES_H
#define CUCURUCHO_COLORES_H

#include <SDL_types.h>
#include <utility>
#include <vector>
#include <tuple>

class ColoresJugador {
public:
    ColoresJugador(std::vector<std::array<int, 3>> base, std::vector<std::array<int, 3>> glow) : base(std::move(base)), glow(std::move(glow)) {}
    std::vector<std::array<int, 3>> base;
    std::vector<std::array<int, 3>> glow;

    std::array<int, 3> getColorGlow(int n) const {
        return glow[n % glow.size()];
    }

};

static const ColoresJugador COLORES_AZUL = ColoresJugador(
        {{32, 0, 239},
         {32, 207, 239},
         {32, 0, 239}},
        {{206, 160, 239},
         {173, 138, 239},
         {140, 101, 239},
         {99, 69, 239},
         {66, 32, 239},
         {33, 0, 206},
         {33, 0, 173},
         {0, 0, 140},
         {0, 0, 99},
         {0, 0, 140},
         {33, 0, 173},
         {33, 0, 206},
         {66, 32, 239},
         {99, 69, 239},
         {140, 101, 239},
         {173, 138, 239}});

static const ColoresJugador COLORES_ROJO = ColoresJugador(
        {{239, 32, 0},
         {239, 207, 0},
         {239, 32, 0}},
        {{239, 206, 160},
         {239, 173, 138},
         {239, 140, 101},
         {239, 99, 69},
         {239, 66, 32},
         {206, 33, 0},
         {173, 33, 0},
         {140, 0, 0},
         {99, 0, 0},
         {140, 0, 0},
         {173, 33, 0},
         {206, 33, 0},
         {239, 66, 32},
         {239, 99, 69},
         {239, 140, 101},
         {239, 173, 138}});


static const ColoresJugador COLORES_ROSA = ColoresJugador(
        {{216, 0, 239},
         {216, 174, 239},
         {216, 0, 239}},
        {{239, 160, 222},
         {245, 134, 220},
         {245, 119, 218},
         {226, 112, 201},
         {216, 57, 181},
         {190, 25, 153},
         {158, 42, 132},
         {108, 32, 91},
         {86, 0, 67},
         {108, 32, 91},
         {158, 42, 132},
         {190, 25, 153},
         {216, 57, 181},
         {226, 112, 201},
         {245, 119, 218},
         {245, 134, 220}});


static const ColoresJugador COLORES_VERDE = ColoresJugador(
        {{33, 210, 30},
         {90, 150, 190},
         {33, 210, 30}},
        {{196, 239, 160},
         {187, 245, 130},
         {182, 245, 119},
         {169, 226, 112},
         {135, 216, 57},
         {110, 190, 24},
         {101, 158, 41},
         {71, 108, 32},
         {41, 86, 0},
         {71, 108, 32},
         {101, 158, 41},
         {110, 190, 24},
         {135, 216, 57},
         {169, 226, 112},
         {182, 245, 119},
         {187, 245, 130}});

static const ColoresJugador COLORES_TURQUESA = ColoresJugador(
        {{120, 120, 120},
         {138, 228, 199},
         {120, 120, 120}},
        {{178, 236, 221},
         {159, 242, 215},
         {151, 242, 211},
         {141, 223, 196},
         {97, 212, 175},
         {68, 187, 143},
         {72, 156, 125},
         {52, 106, 87},
         {21, 83, 65},
         {52, 106, 87},
         {72, 156, 125},
         {68, 187, 143},
         {97, 212, 175},
         {141, 223, 196},
         {151, 242, 211},
         {159, 242, 215}});

#endif //CUCURUCHO_COLORES_H
