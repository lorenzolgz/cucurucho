#ifndef CUCURUCHO_ENEMIGO1_H
#define CUCURUCHO_ENEMIGO1_H


#define ATENUADOR_IA 0.65
#define DISTANCIA_ACTIVADORA_IA 250
#define DISTANCIA_DESACTIVADORA_IA_DERECHA 150
#define DISTANCIA_DESACTIVADORA_IA_IZQUIERDA 80

#include <string>
#include "../../../commons/utils/Vector.h"
#include "Ticker.h"
#include "EntidadEnemigo.h"
#include "Jugador.h"

const int ENEMIGO1_ANCHO = 66;
const int ENEMIGO1_ALTO = 66;


class Enemigo1 : public EntidadEnemigo {
public:
	Enemigo1(float x, float y, float velocidadX);

	Vector getPosicion() override;
	int getAncho() override;
	int getAlto() override;
	void tick() override;
	struct EstadoEnemigo state() override;
	int getTipoEntidad() override;
	std::list<Forma> getFormas() override;
	VidaEntidad* getVidaEntidad() override;
    void aproximarAJugador(std::map<int, Jugador *> jugadores) override;

private:
    Vector posicion;
	float velocidadX;
	VidaEntidad* vida;
};


#endif //CUCURUCHO_ENEMIGO1_H
