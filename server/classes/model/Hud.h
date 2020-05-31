//
// Created by javier on 11/4/20.
//

#ifndef CPP_SANDBOX_HUD_H
#define CPP_SANDBOX_HUD_H


#include "../../../commons/utils/Vector.h"

const int HUD_ANCHO = 960;
const int HUD_ALTO = 96;

class Hud {
public:
    Hud();

	void actualizarHI(int posEnNivel);
	void tick();

private:
	Vector posicion;
	std::string* hi;
};


#endif //CPP_SANDBOX_HUD_H
