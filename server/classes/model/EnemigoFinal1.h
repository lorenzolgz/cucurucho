#ifndef CUCURUCHO_ENEMIGOFINAL1_H
#define CUCURUCHO_ENEMIGOFINAL1_H


#include "EntidadEnemigo.h"

const int ENEMIGO_FINAL1_ANCHO = 375;
const int ENEMIGO_FINAL1_ALTO = 288;

class EnemigoFinal1 : public EntidadEnemigo {
public:
public:
	EnemigoFinal1(float x, float y, float velocidadX, std::map<int, Jugador*>* jugadores);

	EstadoEnemigo state() override;
	float getVelocidadX() override;
	void setPosicion(Vector nuevaPosicion) override;
	void tick() override;
	int getTipoEntidad() override;

private:
	float velocidadX;
};


#endif //CUCURUCHO_ENEMIGOFINAL1_H
